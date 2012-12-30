/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_MSGHEAD_H_
#define _ZH_MSGHEAD_H_

/**
 * 
 *
 * @file zh_msghead.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Wed Dec 26 04:29:04 2012
 *
 **/

#include <stdio.h>

static const unsigned int MAGICNUM = 0xfb709394;

typedef struct zh_msghead {
    unsigned short id;
    unsigned short version;
    unsigned int log_id;
    char provider[16];
    unsigned int magic_num;
    unsigned int reserved;
    unsigned int body_len;
} zh_msghead_t;

int zh_msghead_read(int sock, void *buff, size_t buff_size, int timeout,
                    unsigned int flags);

int zh_msghead_write(int sock, zh_msghead_t *head, int timeout,
                     unsigned int flags);

#endif /* _ZH_MSGHEAD_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
