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

zh_epool_t *zh_epool_open(const int sock_num) {
    if (sock_num < 0) {
        return NULL;
    }

    zh_epool_t *p = (zh_epool_t*)malloc(sizeof(zh_epool_t));
    if (NULL == p) {
        return NULL;
    }

    p->listen_fd = 0;
    p->is_run = 0;
    pthread_mutex_init(&p->job_queue_lock, NULL);
    pthread_cond_init(&p->job_queue_cond, NULL);
    p->job_queue = (struct zh_epool_job*)malloc(sizeof(struct zh_epool_job));
    if (NULL == p->job_queue) {
        ZH_FATAL("memory error");
        goto err;
    }

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
    //p->listen_event = event_new();

    return ZH_SUCC;
}

int zh_epool_start(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    p->is_run = 1;
    event_base_dispatch(p->base);

    return ZH_SUCC;
}

int zh_epool_stop(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    event_base_loopexit(p->base, NULL);
    p->is_run = 0;

    return ZH_SUCC;
}

int zh_epool_is_run(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    return 1 == p->is_run;
}


/* vim: set expandtab shiftwidth=4 tabstop=4: */
