/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_HASH_H_
#define _ZH_HASH_H_

/**
 * 
 *
 * @file zh_hash.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Sep  6 22:31:08 2012
 *
 **/

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "zh_thread.h"

typedef int (*zh_hash_func_t)(uint64_t *hval1_ptr, uint64_t *hval2_ptr);
typedef int (*zh_hash_node_free_func_t)(void *node_ptr);

struct zh_hash_node {
    struct zh_hash_node *next_ptr;
    uint64_t hash_value1;
    uint64_t hash_value2;
    // cache line alignment
    char __align[ZH_CACHE_LINE_ALIGN_SIZE(sizeof(struct zh_hash_node*) +
                                          sizeof(uint64_t) +
                                          sizeof(uint64_t))];
};

typedef struct zh_hash {
    zh_hash_func_t hash_func;
    zh_hash_node_free_func_t node_free_func;
    struct zh_hash_node *bucket;
    int bucket_size;
    int rehash_threshlod;
    pthread_mutex_t rehash_lock;
    pthread_rwlock_t *bucket_lock_vec;
} zh_hash_t;

zh_hash_t *zh_hash_alloc(zh_hash_func_t hash_func,
                         zh_hash_node_free_func_t node_free_func,
                         size_t init_bucket_size);
int zh_hash_free();

int zh_hash_get();
int zh_hash_set();

int zh_hash_delete();

#endif /* _ZH_HASH_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
