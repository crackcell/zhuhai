/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_sock_queue.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Jan 18 19:02:10 2013
 *
 **/

#include <stdlib.h>
#include <zhuhai/zh_log.h>
#include <zhuhai/zh_sock_queue.h>

zh_sock_queue_t* zh_sock_queue_open(const int max_sock_num) {
    if (max_sock_num <= 0) {
        return NULL;
    }

    zh_sock_queue_t *p = (zh_sock_queue_t*)
                         malloc(sizeof(zh_sock_queue_t));
    size_t sz;
    if (NULL == p) {
        ZH_FATAL("can't malloc");
        goto err;
    }

    sz = sizeof(zh_sock_queue_node_t) * max_sock_num;
    p->queue = (zh_sock_queue_node_t*)malloc(sz);
    if (NULL == p->queue) {
        ZH_FATAL("can't malloc");
        goto err;
    }
    bzero(p->queue, sz);

    p->max_sock_num = max_sock_num;

    p->append = 0;
    p->fetch = 0;

    return p;
err:
    zh_sock_queue_close(p);
    return NULL;
}

int zh_sock_queue_close(zh_sock_queue_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    if (p->queue != NULL) {
        free(p->queue);
    }

    return ZH_SUCC;
}

int zh_sock_queue_append(zh_sock_queue_t *p, const int fd) {
    if (NULL == p || fd < 0) {
        return ZH_FAIL;
    }

    int ret = ZH_SUCC;
    int append_pos;
    bool find;

    if (p->sock_num == p->max_sock_num) {
        ZH_DEBUG("queue full");
        ret = ZH_QUEUE_FULL;
        goto out;
    }

    // find an available node
    find = false;
    append_pos = p->append;
    for (int i = 0; i < p->max_sock_num; ++i) {
        append_pos = (append_pos + 1) % p->max_sock_num;
        if (ZH_SOCK_QUEUE_NODE_IDLE == p->queue[append_pos].state) {
            find = true;
            break;
        }
    }

    if (!find) {
        ZH_DEBUG("queue full");
        ret = ZH_QUEUE_FULL;
        p->sock_num = p->max_sock_num;
        goto out;
    }

    p->queue[append_pos].state = ZH_SOCK_QUEUE_NODE_WAIT;
    p->queue[append_pos].fd = fd;
    p->append = append_pos;
    p->sock_num++;

    ZH_DEBUG("insert into pos[%d] with fd[%d]", append_pos, fd);

out:
    return ret;
}

int zh_sock_queue_fetch(zh_sock_queue_t *p, int *fd, int *offset) {
    if (NULL == p || NULL == fd || NULL == offset) {
        return ZH_FAIL;
    }

    int ret = ZH_SUCC;
    int fetch_pos;
    bool find;

    if (0 == p->sock_num) {
        ZH_DEBUG("queue empty");
        ret = ZH_QUEUE_EMPTY;
        goto out;
    }

    find = false;
    fetch_pos = p->fetch;
    for (int i = 0; i < p->max_sock_num; ++i) {
        fetch_pos = (fetch_pos + 1) % p->max_sock_num;
        if (ZH_SOCK_QUEUE_NODE_WAIT == p->queue[fetch_pos].state) {
            find = true;
            break;
        }
    }

    if (!find) {
        ZH_DEBUG("queue empty");
        ret = ZH_QUEUE_EMPTY;
        p->sock_num = 0;
        goto out;
    }

    p->queue[fetch_pos].state = ZH_SOCK_QUEUE_NODE_WORK;
    *fd = p->queue[fetch_pos].fd;
    *offset = fetch_pos;
    p->work_num++;

    ZH_DEBUG("fetch pos[%d] with fd[%d]", fetch_pos, *fd);

out:
    return ret;
}

int zh_sock_queue_reset(zh_sock_queue_t *p, const int offset) {
    if (NULL == p || offset < 0 || offset >= p->max_sock_num) {
        return ZH_FAIL;
    }

    if (p->queue[offset].state != ZH_SOCK_QUEUE_NODE_WORK) {
        return ZH_SUCC;
    }

    p->queue[offset].state = ZH_SOCK_QUEUE_NODE_IDLE;
    p->sock_num--;
    p->work_num--;

    ZH_DEBUG("reset pos[%d] with fd[%d]", offset, p->queue[offset].fd);

    return ZH_SUCC;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
