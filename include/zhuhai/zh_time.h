/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_TIME_H_
#define _ZH_TIME_H_

/**
 * time
 *
 * @file zh_time.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 19:43:21 2012
 *
 **/

#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define ZH_TIME_BUFF_SIZE 32

uint64_t zh_msec_epoch();
time_t zh_sec_epoch();
char *zh_ctime(char *buff, size_t buff_size);

#endif /* _ZH_TIME_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
