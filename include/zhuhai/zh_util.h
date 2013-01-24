/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_UTIL_H_
#define _ZH_UTIL_H_

/**
 * 
 *
 * @file zh_util.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Jan 24 19:33:10 2013
 *
 **/

#include <event2/event.h>

static inline void zh_sock_make_nonblock(int fd) {
    evutil_make_socket_nonblocking(fd);
}

static inline void zh_sock_set_reuseaddr(int fd) {
    int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
}

#endif /* _ZH_UTIL_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
