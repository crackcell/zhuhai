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
 * @file zh_public_1_example.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 10:51:54 2012
 *
 **/

#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>

#include <zhuhai/zh_public.h>

int main(int argc, char *argv[]) {

    char b[] = "t ";
    zh_trim_left(b, sizeof(b));
    printf("[%s]\n", b);

    char b2[] = "  t x";
    zh_trim_left(b2, sizeof(b2));
    printf("[%s]\n", b2);

    char b3[] = "t  ";
    zh_trim_right(b3, sizeof(b3));
    printf("[%s]\n", b3);

    char b4[] = "  t2  ";
    zh_trim(b4, sizeof(b4));
    printf("[%s]\n", b4);

    char b5[] = "";
    zh_trim(b5, sizeof(b5));
    printf("[%s]\n", b5);

    char b6[] = "t ";
    zh_trim(b6, sizeof(b6));
    printf("[%s]\n", b6);

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
