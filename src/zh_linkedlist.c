/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, crackcell <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_linkedlist.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Tue Oct 16 05:54:12 2012
 *
 **/

#include "zh_linkedlist.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>

zh_ret_t zh_linkedlist_init(zh_linkedlist_t *l) {
    if (!l) {
        return ZH_ERR_PARAM;
    }

    l->size = 0;
    l->head_ptr = NULL;
    l->tail_ptr = NULL;

    return ZH_SUCC;
}

zh_ret_t zh_linkedlist_push_front(zh_linkedlist_t *l, void *v) {
    if (!l && !v) {
        return ZH_ERR_PARAM;
    }

    struct zh_linkedlist_node *n = (struct zh_linkedlist_node*)v;
    n->next_ptr = NULL;
    if (l->head_ptr == NULL) {
        l->head_ptr = n;
        l->tail_ptr = n;
    } else {
        n->next_ptr = l->head_ptr;
        l->head_ptr = n;
    }
    l->size++;

    return ZH_SUCC;
}

zh_ret_t zh_linkedlist_push_back(zh_linkedlist_t *l, void *v) {
    if (!l && !v) {
        return ZH_ERR_PARAM;
    }

    struct zh_linkedlist_node *n = (struct zh_linkedlist_node*)v;
    n->next_ptr = NULL;
    if (l->tail_ptr == NULL) {
        l->head_ptr = n;
        l->tail_ptr = n;
    } else {
        l->tail_ptr->next_ptr = n;
        l->tail_ptr = l->tail_ptr->next_ptr;
    }
    l->size++;

    return ZH_SUCC;
}

void *zh_linkedlist_front(zh_linkedlist_t *l) {
    if (!l) {
        return NULL;
    }

    return l->head_ptr;
}

void *zh_linkedlist_back(zh_linkedlist_t *l) {
    if (!l) {
        return NULL;
    }

    return l->tail_ptr;
}

void *zh_linkedlist_at(zh_linkedlist_t *l, const int i) {
    if (!l || i < 0 || i >= l->size) {
        return NULL;
    }

    int k = 0;
    struct zh_linkedlist_node *n = l->head_ptr;
    while (n != NULL && k < i) {
        n = n->next_ptr;
        k++;
    }

    return k < i ? NULL : n;
}

zh_ret_t zh_linkedlist_clear(zh_linkedlist_t *l) {
    if (!l) {
        return ZH_ERR_PARAM;
    }

    struct zh_linkedlist_node *n;
    while ((n = l->head_ptr)!= NULL) {
        l->head_ptr = n->next_ptr;
        free(n);
    }
    l->size = 0;

    return ZH_SUCC;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
