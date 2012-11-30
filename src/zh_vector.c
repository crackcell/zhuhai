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
 * @file zh_vector.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Nov 30 21:00:11 2012
 *
 **/

#include "zh_vector.h"

#include <stdio.h>
#include <stdlib.h>

static void free_slots(zh_vector_t *ptr);

zh_vector_t *zh_vector_alloc() {
    zh_vector_t *ptr = (zh_vector_t*)malloc(sizeof(zh_vector_t));
    ptr->node_count = 0;
    ptr->slot_count = 0;
    ptr->slots = NULL;
    return ptr;
}

int zh_vector_free(zh_vector_t *ptr) {
    free_slots(ptr);
    free(ptr);

    return ZH_SUCC;
}

int zh_vector_push_front(zh_vector_t *ptr, void *val, size_t size);
int zh_vector_push_back(zh_vector_t *ptr, void *val, size_t size);

/***************************************************************/

static void free_slots(zh_vector_t *ptr) {
    int i;
    for (i = 0; i < ptr->slot_count; i++) {
        struct zh_vector_slot *slot_ptr = &(ptr->slots[i]);
        free(slot_ptr->ptr);
        slot_ptr->size = 0;
    }
    ptr->slot_count = 0;
    free(ptr->slots);
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
