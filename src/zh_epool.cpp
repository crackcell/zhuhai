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

#include <stdlib.h>
#include <zhuhai/common.h>
#include <zhuhai/zh_epool.h>
#include <zhuhai/zh_log.h>

static void accept_cb(int listen_fd, short event, void *arg);
static int initqueue(zh_epool_t *p);
static int enqueue(zh_epool_t *p, struct zh_epool_job *job);

zh_epool_t *zh_epool_open(const int max_job_num) {
    if (max_job_num < 0) {
        return NULL;
    }

    zh_epool_t *p = (zh_epool_t*)malloc(sizeof(zh_epool_t));
    if (NULL == p) {
        return NULL;
    }

    p->listen_fd = 0;
    p->is_run = 0;
    p->max_job_num = max_job_num;
    pthread_mutex_init(&p->job_queue_lock, NULL);
    pthread_cond_init(&p->job_queue_cond, NULL);
    p->job_queue = (struct zh_epool_job*)malloc(sizeof(struct zh_epool_job) * max_job_num);
    if (NULL == p->job_queue) {
        ZH_FATAL("memory error");
        goto err;
    }
    initqueue(p);

    p->base = event_base_new();
    if (NULL == p->base) {
        ZH_FATAL("alloc event base fail");
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
    if (p->job_queue != NULL) {
        delete p->job_queue;
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
    p->listen_event = event_new(p->base, fd, EV_READ | EV_PERSIST, accept_cb, (void*)p);
    event_add(p->listen_event, NULL);

    return ZH_SUCC;
}

int zh_epool_start(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    ZH_DEBUG("loop starts");
    p->is_run = 1;
    event_base_dispatch(p->base);

    return ZH_SUCC;
}

int zh_epool_stop(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    ZH_DEBUG("loop stops");
    event_base_loopexit(p->base, NULL);
    p->is_run = 0;

    return ZH_SUCC;
}

static void accept_cb(int listen_fd, short event, void *arg) {
    zh_epool_t *p = (zh_epool_t*)arg;
    static int count = 0;
    ++count;
    if (count == 3) {
        zh_epool_stop(p);
    }
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listen_fd, (struct sockaddr*)&ss, &slen);
    if (fd < 0) {
        // TODO print log
    } else {
        struct zh_epool_job job;
        job.sock = fd;
        gettimeofday(&job.in_queue_time, NULL);
        enqueue(p, &job);
        ZH_DEBUG("client comes, in_time[%d]", *(int*)(&job.in_queue_time));
        const char *msg = "hello world\n";
        send(fd, msg, strlen(msg) + 1, 0);
        close(fd);
    }
}

static int initqueue(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    p->job_head = 0;
    p->job_tail = 0;

    return ZH_SUCC;
}

static int enqueue(zh_epool_t *p, struct zh_epool_job *job) {
    if (NULL == p || NULL == job) {
        return ZH_FAIL;
    }

    pthread_mutex_lock(&p->job_queue_lock);

    int insert_pos = (p->job_tail + 1) % p->max_job_num;

    if (insert_pos == p->job_head) {
        ZH_DEBUG("job queue full");
        goto err;
    }
    p->job_queue[insert_pos] = *job;
    ZH_DEBUG("epool: pos[%d]=fd[%d]", insert_pos, job->sock);

    p->job_tail = insert_pos;
    pthread_mutex_unlock(&p->job_queue_lock);
    return ZH_SUCC;
err:
    pthread_mutex_unlock(&p->job_queue_lock);
    return ZH_FAIL;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
