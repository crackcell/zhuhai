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

    pthread_mutex_t sock_queue_lock;
    std::deque<struct zh_epool_job> *sock_queue_ptr;

    int is_run;
} zh_epool_t;

zh_epool_t *zh_epool_open();
int zh_epool_close(zh_epool_t *p);

int zh_epool_set_listen_fd(zh_epool_t *p, const int fd);

int zh_epool_start(zh_epool_t *p);
int zh_epool_stop(zh_epool_t *p);
int zh_epool_is_run(zh_epool_t *p);

int zh_epool_fetch_item(zh_epool_t *p, int *offset, int &fd);
int zh_epool_reset_item(zh_epool_t *p, const int offset);

// check timeout
int zh_epool_check_item(zh_epool_t *p);

#endif /* _ZH_EPOOL_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
