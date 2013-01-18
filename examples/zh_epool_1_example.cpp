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
#include <zhuhai/zh_util.h>

int main(int argc, char *argv[]) {
    int listen_fd;
    struct sockaddr_in sin;

    zh_epool_t *p = zh_epool_open(3);

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(9001);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    zh_sock_make_nonblock(listen_fd);
    zh_sock_set_reuseaddr(listen_fd);

    if (bind(listen_fd, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("bind");
    }

    if (listen(listen_fd, 16) < 0) {
        perror("listen");
    }

    zh_epool_set_listen_fd(p, listen_fd);
    zh_epool_start(p);

    zh_epool_close(p);
    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
