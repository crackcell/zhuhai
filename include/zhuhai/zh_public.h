/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_PUBLIC_H_
#define _ZH_PUBLIC_H_

/**
 * 
 *
 * @file zh_public.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Tue Jun  5 11:12:09 2012
 *
 **/

#include "zh_error.h"

#ifndef likely
#define likely(x)       __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x)     __builtin_expect(!!(x), 0)
#endif

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifndef ZH_LINE_BUFF_SIZE
#define ZH_LINE_BUFF_SIZE 1024
#endif

static inline int zh_trim_left(char *buff, int size) {
    if (NULL == buff || size < 0) {
        return ZH_FAIL;
    }

    int acc = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (' ' == buff[i] || '\t' == buff[i]) {
            ++acc;
        } else {
            break;
        }
    }

    // move char forward
    if (0 == acc || acc == size) {
        return ZH_SUCC;
    }
    for (i = acc; i < size; i++) {
        buff[i - acc] = buff[i];
        if ('\0' == buff[i - acc]) {
            break;
        }
    }

    return ZH_SUCC;
}

static inline int zh_trim_right(char *buff, int size) {
    if (NULL == buff || size < 0) {
        return ZH_FAIL;
    }

    int acc = 0;
    int i;
    for (i = size - 1; i >= 0; i--) {
        if (' ' == buff[i] || '\t' == buff[i] || '\0' == buff[i] ||
            '\n' == buff[i]) {
            ++acc;
        } else {
            break;
        }
    }

    // truncate string
    if (0 == acc) {
        return ZH_SUCC;
    }
    buff[size - acc] = '\0';

    return ZH_SUCC;
}

static inline int zh_trim(char *buff, int size) {
    if (NULL == buff || size < 0) {
        return ZH_FAIL;
    }

    if (zh_trim_left(buff, size) == ZH_FAIL) {
        return ZH_FAIL;
    }

    if (zh_trim_right(buff, size) == ZH_FAIL) {
        return ZH_FAIL;
    }

    return ZH_SUCC;
}

#endif /* _ZH_PUBLIC_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
