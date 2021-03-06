/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_ERROR_H_
#define _ZH_ERROR_H_

/**
 * Error handling functions
 *
 * @file zh_error.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Oct 15 11:38:55 2012
 *
 **/

typedef enum {
    ZH_SUCC = 0,
    ZH_FAIL,
    ZH_ERR_PARAM,
    ZH_QUEUE_FULL,
    ZH_QUEUE_EMPTY,
    ZH_RETCODE_NUM,
} zh_ret_t;

const char *zh_strerror(int errnum);

#endif /* _ZH_ERROR_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
