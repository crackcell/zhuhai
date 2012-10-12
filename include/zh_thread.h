/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_THREAD_H_
#define _ZH_THREAD_H_

/**
 * thread
 *
 * @file zh_thread.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 17:33:54 2012
 *
 **/

#include <stdint.h>

#ifdef x86_64
#define ZH_CACHE_LINE_SIZE 64
#endif
#ifdef armv7l
#define ZH_CACHE_LINE_SIZE 32
#endif

#define ZH_CACHE_LINE_ALIGN_SIZE(size) \
    (((((size) - 1) / ZH_CACHE_LINE_SIZE) + 1) * ZH_CACHE_LINE_SIZE)

uint64_t get_tid_self();

#endif /* _ZH_THREAD_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
