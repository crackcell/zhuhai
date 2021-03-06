/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * Pending pool with libevent
 *
 * @file zh_epool.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Jan 14 20:57:49 2013
 *
 **/

#include <string.h>
#include <stdlib.h>
#include <zhuhai/zh_error.h>
#include <zhuhai/zh_epool.h>

static void accept_cb(int listen_fd, short event, void *arg);

static int queue_append(zh_epool_t *p, const int fd);
static int queue_fetch(zh_epool_t *p, int *fd, int *offset);
static int queue_reset(zh_epool_t *p, const int offset);

zh_epool_t *zh_epool_open(const int max_job_num) {
    if (max_job_num <= 0) {
        return NULL;
    }

    zh_epool_t *p = (zh_epool_t*)malloc(sizeof(zh_epool_t));
    if (NULL == p) {
        return NULL;
    }

    p->listen_fd = 0;
    p->is_run = 0;

    pthread_mutex_init(&p->sock_queue_lock, NULL);
    pthread_cond_init(&p->sock_queue_cond, NULL);

    p->sock_queue = zh_sock_queue_open(max_job_num);
    if (NULL == p->sock_queue) {
        fprintf(stderr, "memory error");
        goto err;
    }

    p->base = event_base_new();
    if (NULL == p->base) {
        fprintf(stderr, "alloc event base fail");
        goto err;
    }

    return p;
err:
    if (p != NULL) {
        zh_epool_close(p);
    }
    return NULL;
}

int zh_epool_close(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }
    if (p->sock_queue != NULL) {
        zh_sock_queue_close(p->sock_queue);
    }
    if (p->base != NULL) {
        event_base_free(p->base);
    }
    free(p);
    return ZH_SUCC;
}

int zh_epool_set_listen_fd(zh_epool_t *p, const int fd) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    p->listen_fd = fd;
    p->listen_event = event_new(p->base, fd, EV_READ | EV_PERSIST, accept_cb,
                                (void*)p);
    event_add(p->listen_event, NULL);

    return ZH_SUCC;
}

int zh_epool_start(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    fprintf(stderr, "loop starts");
    p->is_run = 1;
    event_base_dispatch(p->base);

    return ZH_SUCC;
}

int zh_epool_stop(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    fprintf(stderr, "loop stops");
    event_base_loopexit(p->base, NULL);
    p->is_run = 0;

    return ZH_SUCC;
}

int zh_epool_fetch_item(zh_epool_t *p, int *offset, int *fd) {
    if (NULL == p || NULL == offset || NULL == fd) {
        return ZH_FAIL;
    }
    // TODO: check cond variable
    return queue_fetch(p, offset, fd);
}

int zh_epool_reset_item(zh_epool_t *p, const int offset) {
    if (NULL == p || offset < 0) {
        return ZH_FAIL;
    }
    return queue_reset(p, offset);
}


/***************************************************************/

static void accept_cb(int listen_fd, short event, void *arg) {
    zh_epool_t *p = (zh_epool_t*)arg;
    static int count = 0;
    ++count;
    if (count == 5) {
        zh_epool_stop(p);
    }
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listen_fd, (struct sockaddr*)&ss, &slen);
    if (fd < 0) {
        // TODO print log
    } else {
        fprintf(stderr, "client comes");

        const char *msg;
        switch (queue_append(p, fd)) {
        case ZH_SUCC:
            msg = "\nmsg: hello world\n";
            send(fd, msg, strlen(msg) + 1, 0);
            break;
        case ZH_QUEUE_FULL:
            msg = "\nerr: queue full\n";
            send(fd, msg, strlen(msg) + 1, 0);
            break;
        default:
            msg = "\nerr: unknown\n";
            send(fd, msg, strlen(msg) + 1, 0);
            break;
        }
        //close(fd);
    }
}

static int queue_append(zh_epool_t *p, const int fd) {
    if (NULL == p || fd < 0) {
        return ZH_FAIL;
    }

    pthread_mutex_lock(&p->sock_queue_lock);
    int ret = zh_sock_queue_append(p->sock_queue, fd);
    pthread_mutex_unlock(&p->sock_queue_lock);
    pthread_cond_signal(&p->sock_queue_cond);

    return ret;
}

static int queue_fetch(zh_epool_t *p, int *fd, int *offset) {
    if (NULL == p || NULL == fd || NULL == offset) {
        return ZH_FAIL;
    }

    pthread_mutex_lock(&p->sock_queue_lock);
    while (p->sock_queue->sock_num - p->sock_queue->work_num <= 0) {
        pthread_cond_wait(&p->sock_queue_cond, &p->sock_queue_lock);
    }
    int ret = zh_sock_queue_fetch(p->sock_queue, fd, offset);
    pthread_mutex_unlock(&p->sock_queue_lock);

    return ret;
}

static int queue_reset(zh_epool_t *p, const int offset) {
    if (NULL == p || offset < 0) {
        return ZH_FAIL;
    }

    pthread_mutex_lock(&p->sock_queue_lock);
    int ret = zh_sock_queue_reset(p->sock_queue, offset);
    pthread_mutex_unlock(&p->sock_queue_lock);

    return ret;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
