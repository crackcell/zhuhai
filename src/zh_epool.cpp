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
 * 
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

zh_epool_t *zh_epool_open(const int sock_num,
                          const int connect_timeout,
                          const int read_timeout, const int write_timeout) {
    zh_epool_t *p = (zh_epool_t*)malloc(sizeof(zh_epool_t));
    if (NULL == p) {
        return NULL;
    }

    p->connect_timeout = connect_timeout;
    p->read_timeout = read_timeout;
    p->write_timeout = write_timeout;
    p->is_run = 0;
    p->sock_num = sock_num;
    p->sock_array = (int*)malloc(sizeof(int) * sock_num);
    if (NULL == p->sock_array) {
        ZH_FATAL("memory error");
        goto err;
    }

    return p;
err:
    if (p != NULL) {
        free(p);
    }
    return NULL;
}

int zh_epool_close(zh_epool_t *p) {
    free(p);
    return ZH_SUCC;
}

int zh_epool_set_listen_fd(zh_epool_t *p, const int fd) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    p->listen_fd = fd;

    return ZH_SUCC;
}

int zh_epool_start(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    p->is_run = 1;

    return ZH_SUCC;
}

int zh_epool_stop(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    p->is_run = 0;
    // TODO: reset all socks

    return ZH_SUCC;
}

int zh_epool_is_run(zh_epool_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    return 1 == p->is_run;
}


/* vim: set expandtab shiftwidth=4 tabstop=4: */
