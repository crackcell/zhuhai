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
 * @file zh_atomic_2_example.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Oct 18 03:44:42 2012
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <zh_atomic.h>

static const int g_count = 10000000;

int a() {
    zh_atomic_t a;
    int k;
    int i;
    zh_atomic_set(&a, g_count);
    for (i = 0; i < g_count; i++) {
        k = zh_atomic_dec_test(&a, 1);
    }
    return k;
}

int b() {
    int a = g_count;
    int k;
    int i;
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    for (i = 0; i < g_count; i++) {
        pthread_mutex_lock(&m);
        a--;
        k = a == 0;
        pthread_mutex_unlock(&m);
    }
    pthread_mutex_destroy(&m);
    return k;
}

int main(int argc, char *argv[]) {
    if (argc == 2 && atoi(argv[1]) == 0) {
        a();
    } else {
        b();
    }
    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
