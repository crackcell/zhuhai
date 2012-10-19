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
 * @file zh_atomic_1_example.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Oct 18 03:44:42 2012
 *
 **/

#include <stdio.h>
#include <zh_atomic.h>

int main(int argc, char *argv[]) {
    zh_atomic_t a;
    zh_atomic_set(&a, 0);
    printf("%d\n", a.counter);
    zh_atomic_set(&a, 1000);
    printf("%d\n", a.counter);
    zh_atomic_inc(&a);
    printf("%d\n", a.counter);
    int k = zh_atomic_add_return(&a, 2);
    printf("%d\n", k);

    zh_atomic_set(&a, 1);
    printf("is 0: %d\n", zh_atomic_dec_and_test(&a, 1));

    zh_atomic_add(&a, 1);

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
