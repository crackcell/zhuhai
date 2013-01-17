/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_epool_1_example.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Jan 17 21:03:41 2013
 *
 **/

#include <stdio.h>
#include <zhuhai/zh_epool.h>

int main(int argc, char *argv[]) {
    zh_epool_t *p = zh_epool_open(100);
    zh_epool_close(p);
    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
