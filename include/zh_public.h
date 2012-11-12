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

#ifdef __cplusplus
extern "C" {
#endif

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#ifdef __cplusplus
}
#endif

#endif /* _ZH_PUBLIC_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
