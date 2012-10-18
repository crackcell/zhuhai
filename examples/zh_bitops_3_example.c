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
 * @file zh_bitops_1_example.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Wed Oct 17 04:09:28 2012
 *
 **/

#include <stdio.h>
#include <time.h>
#include <zh_bitops.h>

int main(int argc, char *argv[]) {
    long int a = 2;
    printf("%d\n", zh_test_bit(&a, 0));
    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
