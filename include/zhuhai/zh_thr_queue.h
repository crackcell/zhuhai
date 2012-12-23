/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_THR_QUEUE_H_
#define _ZH_THR_QUEUE_H_

/**
 * 
 *
 * @file zh_thr_queue.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 15:32:52 2012
 *
 **/

#include <queue>
#include <vector>
#include <zhuhai/zh_meta.h>

typedef struct zh_thr_queue_node {
    void *p;
    struct zh_thr_queue_node *next_ptr;
} zh_thr_queue_node_t;

typedef void*(*zh_thr_queue_node_alloc_func_t)(void *arg);
typedef int(*zh_thr_queue_node_free_func_t)(void *arg);
typedef int(*zh_thr_queue_node_less_func_t)(void *a, void *b);

typedef struct zh_thr_queue_callback {
    size_t node_size;
    zh_thr_queue_node_alloc_func_t node_alloc_func;
    zh_thr_queue_node_free_func_t node_free_func;
    zh_thr_queue_node_less_func_t node_less_func;
} zh_thr_queue_callback_t;

bool operator<(const zh_thr_queue_node_t &a, const zh_thr_queue_node_t &b) {
    return true;
}

bool operator>(const zh_thr_queue_node_t &a, const zh_thr_queue_node_t &b) {
    return true;
}

typedef std::priority_queue<zh_thr_queue_node_t,
        std::vector<zh_thr_queue_node_t>,
        std::less<std::vector<zh_thr_queue_node_t>::value_type> >
        zh_thr_queue_type_t;

typedef struct zh_thr_queue {
    zh_meta_t meta;
    zh_thr_queue_type_t *queue_ptr;
} zh_thr_queue_t;

zh_thr_queue_t *zh_thr_queue_open(zh_thr_queue_callback_t cb, const char *name);
int zh_thr_queue_close(zh_thr_queue_t *p);

int zh_thr_queue_insert(zh_thr_queue_t *p, void *n);
int zh_thr_queue_fetch(zh_thr_queue_t *p, void *buff, size_t size);

#endif /* _ZH_THR_QUEUE_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
