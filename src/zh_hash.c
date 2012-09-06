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
 * @file zh_hash.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Sep  6 23:01:14 2012
 *
 **/

#include "zh_hash.h"

static size_t g_prime_table[] = {
    11, 13, 17, 19, 23, 29, 31
    /* TODO: add more primes */
};

zh_hash_t zh_hash_alloc(zh_hash_func_t hash_func,
                        zh_hash_node_free_func_t node_free_func,
                        size_t init_bucket_size) {

    struct zh_hash *hash_ptr = (struct zh_hash*)malloc(sizeof(struct zh_hash));
    if (NULL == hash_ptr) {
        goto error;
    }

    for (size_t i = 0; i < sizeof(g_prime_table) / sizeof(size_t); i++) {
        if (g_prime_table[i] > init_bucket_size) {
            init_bucket_size = g_prime_table[i];
            break;
        }
    }
    hash_ptr->bucket_size;

    hash_ptr->bucket =
            (struct zh_hash_node*)malloc(
                sizeof(struct zh_hash_node) * init_bucket_size);
    hash_ptr->bucket_lock_vec =
            (pthread_mutex_lock*)malloc(
                sizeof(pthread_mutex_lock) * init_bucket_size);
    if (NULL == hash_ptr->bucket || NULL == hash_ptr->bucket_lock_vec) {
        goto error;
    }

    hash_ptr->hash_func = hash_func;
    hash_ptr->node_free_func = node_free_func;

    return hash_ptr;
error:
    if (hash_ptr != NULL) {
        if (hash_ptr->bucket != NULL) {
            free(hash_ptr->bucket);
            hash_ptr->bucket = NULL;
        }
        free(hash_ptr);
    }
    return NULL;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
