/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_LINKEDLIST_H_
#define _ZH_LINKEDLIST_H_

/**
 * 
 *
 * @file zh_linkedlist.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Oct 15 13:39:00 2012
 *
 **/

#include "zh_public.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct zh_linkedlist_node {
    struct zh_linkedlist_node *next_ptr;
} zh_linkedlist_node_t;

typedef struct {
    int size;
    struct zh_linkedlist_node *head_ptr;
    struct zh_linkedlist_node *tail_ptr;
    struct zh_linkedlist_node *free_ptr;
} zh_linkedlist_t;

zh_ret_t zh_linkedlist_init(zh_linkedlist_t *l);

zh_ret_t zh_linkedlist_push_front(zh_linkedlist_t *l, void *v);
zh_ret_t zh_linkedlist_push_back(zh_linkedlist_t *l, void *v);

zh_ret_t zh_linkedlist_delete(zh_linkedlist_t *l, const int i);

void *zh_linkedlist_back(zh_linkedlist_t *l);
void *zh_linkedlist_front(zh_linkedlist_t *l);

void *zh_linkedlist_at(zh_linkedlist_t *l, const int i);

zh_ret_t zh_linkedlist_clear(zh_linkedlist_t *l);

#ifdef __cplusplus
}
#endif

#endif /* _ZH_LINKEDLIST_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
