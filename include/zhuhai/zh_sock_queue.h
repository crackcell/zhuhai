/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_SOCK_QUEUE_H_
#define _ZH_SOCK_QUEUE_H_

/**
 * 
 *
 * @file zh_sock_queue.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Jan 18 02:18:11 2013
 *
 **/

#include <sys/time.h>
#include <pthread.h>
#include <zhuhai/zh_thread.h>

typedef enum {
    ZH_SOCK_QUEUE_NODE_IDLE = 0,
    ZH_SOCK_QUEUE_NODE_WAIT,
    ZH_SOCK_QUEUE_NODE_WORK
} zh_sock_queue_node_state_t;

typedef struct {
    int fd;
    zh_sock_queue_node_state_t state;
    struct timeval in_time;
    ZH_CACHE_LINE_ALIGN(sizeof(int) +
                        sizeof(zh_sock_queue_node_state_t) +
                        sizeof(struct timeval));
} zh_sock_queue_node_t;

typedef struct {
    int max_sock_num;
    int sock_num;
    int work_num;
    zh_sock_queue_node_t *queue;
    int append;
    int fetch;
} zh_sock_queue_t;

zh_sock_queue_t* zh_sock_queue_open(const int max_sock_num);
int zh_sock_queue_close(zh_sock_queue_t *p);

int zh_sock_queue_append(zh_sock_queue_t *p, const int fd);
int zh_sock_queue_fetch(zh_sock_queue_t *p, int *fd, int *offset);
int zh_sock_queue_reset(zh_sock_queue_t *p, const int offset);

#endif /* _ZH_SOCK_QUEUE_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
