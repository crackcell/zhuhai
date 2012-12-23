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
 * example for zh_log
 *
 * @file zh_log_example.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sat Sep  1 01:29:59 2012
 *
 **/

#include <zhuhai/zh_log.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg_ptr) {
    zh_log_open_r();
    //int count = 0;
    //while (1) {
    //count++;
    zh_log_write(ZH_LOG_NOTICE, "hello");
    sleep(1);
    zh_log_close_r();
    //}
    return NULL;
}

int main(int argc, char *argv[]) {
    zh_log_open("test", ".", "test_file", ZH_LOG_ALL);
    zh_log_write(ZH_LOG_DEBUG, "main thread starts");

    pthread_t p[10];
    size_t i;
    for (i = 0; i < sizeof(p) / sizeof(pthread_t); i++) {
        pthread_create(&(p[i]), NULL, thread_func, NULL);
    }

    for (i = 0; i < sizeof(p) / sizeof(pthread_t); i++) {
        pthread_join(p[i], NULL);
    }

    zh_log_close();

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
