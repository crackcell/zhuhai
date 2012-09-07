/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_THR_QUEUE_H_
#define _ZH_THR_QUEUE_H_

/**
 * Lookfree queue between threads
 *
 * @file zh_thr_queue.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Sep  7 14:35:47 2012
 *
 **/

#include <stdio.h>

#define ZH_THR_QUEUE_MAX_NAME 256

struct zh_thr_queue {
    char queue_name[ZH_THR_QUEUE_MAX_NAME];
};
typedef struct zh_thr_queue zh_thr_queue_t;

#endif /* _ZH_THR_QUEUE_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
