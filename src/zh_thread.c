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
 * @file zh_thread.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Tue Jun  5 08:56:14 2012
 *
 **/

#include "zh_thread.h"

#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

uint64_t get_tid_self() {
    uint64_t tid;
#ifdef Darwin
    pthread_t ptid = pthread_self();
    tid = pthread_threadid_np(ptid, &tid);
#else
  #ifdef Linux
    #ifndef __NR_gettid
    #define __NR_gettid 224
    #endif
    tid = syscall(__NR_gettid);
  #endif
#endif
    return tid;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
