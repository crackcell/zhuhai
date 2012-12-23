/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_thr_queue.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 21:08:54 2012
 *
 **/

#include <zhuhai/zh_thr_queue.h>
#include <zhuhai/zh_public.h>
#include <zhuhai/zh_meta.h>

zh_thr_queue_t *zh_thr_queue_open(zh_thr_queue_callback_t cb,
                                  const char *name) {
    if (NULL == cb.node_alloc_func || NULL == cb.node_free_func ||
        NULL == cb.node_less_func || cb.node_size <= 0) {
        return NULL;
    }

    zh_thr_queue_t *p = (zh_thr_queue_t*)malloc(sizeof(zh_thr_queue_t));
    if (NULL == p) {
        return NULL;
    }

    if (NULL == name) {
        zh_meta_set_name(p, g_s_null_name);
    } else {
        zh_meta_set_name(p, name);
    }

    p->queue_ptr = new (std::nothrow) zh_thr_queue_type_t;
    if (NULL == p->queue_ptr) {
        goto err;
    }

    p->node_alloc_func = cb.node_alloc_func;
    p->node_free_func = cb.node_free_func;
    p->node_less_func = cb.node_less_func;
    p->node_size = cb.node_size;

    return p;
err:
    if (p != NULL) {
        if (p->queue_ptr != NULL) {
            delete p->queue_ptr;
            p->queue_ptr = NULL;
        }
        free(p);
        p = NULL;
    }

    return NULL;
}

int zh_thr_queue_close(zh_thr_queue_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    if (p->queue_ptr != NULL) {
        delete p->queue_ptr;
        p->queue_ptr = NULL;
    }
    free(p);

    return ZH_SUCC;
}

int zh_thr_queue_insert(zh_thr_queue_t *p, void *n) {
    return ZH_SUCC;
}

int zh_thr_queue_fetch(zh_thr_queue_t *p, void *buff, size_t size) {
    return ZH_SUCC;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
