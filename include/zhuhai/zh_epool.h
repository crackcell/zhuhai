/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_EPOOL_H_
#define _ZH_EPOOL_H_

/**
 * 
 *
 * @file zh_epool.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 24 20:43:38 2012
 *
 **/

#include <sys/time.h>
#include <event2/event.h>
#include <pthread.h>
#include <deque>

struct zh_epool_job {
    int sock;
    struct timeval in_queue_time;
};

typedef struct {
    int listen_fd;
    struct event_base *base;
    struct event *listen_event;

    int max_wait_num;
    pthread_mutex_t wait_queue_lock;
    std::deque<struct zh_epool_job> *wait_queue;

    int max_work_num;
    pthread_mutex_t work_queue_lock;
    pthread_cond_t work_queue_cond;
    std::deque<struct zh_epool_job> *work_queue;

    int is_run;
} zh_epool_t;

/**
 * Create a new epool.
 *
 * @param [in] max_job_num max number of jobs the pool can process 
 *             at the same time.
 * @return ZH_SUCC if successful, or ZH_FAIL if an error occurred.
 * @see zh_epool_close()
 */
zh_epool_t *zh_epool_open(const int max_wait_num, const int max_work_num);

/**
 * Destroys a epool.
 *
 * @param [in/out] p a pointer to a epool struct.
 * @return ZH_SUCC if successful, or ZH_FAIL if an error occurred.
 * @see zh_epool_open()
 */
int zh_epool_close(zh_epool_t *p);

int zh_epool_set_listen_fd(zh_epool_t *p, const int fd);

int zh_epool_start(zh_epool_t *p);
int zh_epool_stop(zh_epool_t *p);

/**
 * Check whether a pool is running.
 *
 * @param [in] p a pointer to a zh_epool_t struct
 * @return ZH_SUCC if successful, or ZH_FAIL if an error occurred.
 */
static inline int zh_epool_is_run(zh_epool_t *p) {
    return NULL == p ? 0 : 1 == p->is_run;
}

int zh_epool_fetch_item(zh_epool_t *p, int *offset, int &fd);
int zh_epool_reset_item(zh_epool_t *p, const int offset);

// check timeout
int zh_epool_check_item(zh_epool_t *p);

#endif /* _ZH_EPOOL_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
