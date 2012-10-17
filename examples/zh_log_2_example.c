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

#include "zh_log.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *thread_func(void *arg_ptr) {
    zh_openlog_r();
    int count = 0;
    while (1) {
        count++;
        zh_writelog(ZH_LOG_NOTICE, "%d", count);
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    zh_openlog("test", ".", "test_file", ZH_LOG_ALL);
    zh_writelog(ZH_LOG_DEBUG, "main thread starts");

    pthread_t p[10];
    int i;
    for (i = 0; i < 10; i++) {
        pthread_create(&(p[i]), NULL, thread_func, NULL);
    }

    for (i = 0; i < 10; i++) {
        pthread_join(p[i], NULL);
    }

    zh_closelog();

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
