/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_VECTOR_H_
#define _ZH_VECTOR_H_

/**
 * 
 *
 * @file zh_vector.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Nov 29 10:36:35 2012
 *
 **/

#include <stdlib.h>

#include "zh_public.h"

#ifdef __cplusplus
extern "C" {
#endif

struct zh_vector_slot {
    size_t size;
    void *ptr;
    struct zh_vector_slot *next_slot;
};

typedef struct zh_vector {
    int node_count;
    int slot_count;
    struct zh_vector_slot *slots;
} zh_vector_t;

zh_vector_t *zh_vector_alloc();

int zh_vector_free(zh_vector_t *ptr);

int zh_vector_push_front(zh_vector_t *ptr, void *val, size_t size);
int zh_vector_push_back(zh_vector_t *ptr, void *val, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* _ZH_VECTOR_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
