/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_JOB_QUEUE_H_
#define _ZH_JOB_QUEUE_H_

/**
 * 
 *
 * @file zh_job_queue.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Jan 18 02:18:11 2013
 *
 **/



typedef struct {
    zh_job_queue_func_t func;

    std::deque wait_queue<>
    struct zh_job_rawqueue wait_queue;
    struct zh_job_rawqueue work_queue;
} zh_job_queue_t;


#endif /* _ZH_JOB_QUEUE_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
