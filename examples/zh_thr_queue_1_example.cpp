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
 * @file zh_thr_queue_1_example.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 24 03:00:43 2012
 *
 **/

#include <zhuhai/zh_thr_queue.h>
#include <zhuhai/zh_log.h>

int main(int argc, char *argv[]) {
    zh_thr_queue_t *p;
    zh_thr_queue_callback_t cb;
    p = zh_thr_queue_open(cb, "test_queue");
    if (NULL == p) {
        ZH_FATAL("open queue fail.");
        goto err;
    }
    if (zh_thr_queue_close(p) == ZH_FAIL) {
        ZH_FATAL("close queue fail.");
    }

    return 0;
err:
    if (p != NULL) {
        zh_thr_queue_close(p);
        p = NULL;
    }
    return 1;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
