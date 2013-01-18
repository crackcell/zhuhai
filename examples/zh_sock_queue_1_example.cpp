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
 * @file zh_sock_queue_1_example.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Jan 18 21:10:35 2013
 *
 **/

#include <stdio.h>
#include <zhuhai/zh_sock_queue.h>

int main(int argc, char *argv[]) {
    zh_sock_queue_t *p = zh_sock_queue_open(3);
    printf("append 5 items\n");
    for (int i = 0; i < 5; ++i) {
        zh_sock_queue_append(p, i);
    }

    int fd;
    int offset;
    printf("fetch 4 items\n");
    zh_sock_queue_fetch(p, &fd, &offset);
    zh_sock_queue_fetch(p, &fd, &offset);
    zh_sock_queue_fetch(p, &fd, &offset);
    zh_sock_queue_fetch(p, &fd, &offset);

    printf("reset 2 items\n");
    for (int i = 0; i < 2; ++i) {
        zh_sock_queue_reset(p, i);
    }

    printf("append 5 items\n");
    for (int i = 0; i < 5; ++i) {
        zh_sock_queue_append(p, i);
    }

    zh_sock_queue_close(p);
    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
