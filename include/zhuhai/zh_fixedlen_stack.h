/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_FIXEDLEN_STACK_H_
#define _ZH_FIXEDLEN_STACK_H_

/**
 * Fixed-length stack implementation
 *
 * @file zh_fixedlen_stack.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Jan 13 05:15:33 2013
 *
 **/

typedef struct {
    int size;
    int *array;
} zh_fixedlen_stack_t;

#endif /* _ZH_FIXEDLEN_STACK_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
