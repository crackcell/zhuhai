/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_LOG_COMMON_H_
#define _ZH_LOG_COMMON_H_

/**
 * 
 *
 * @file zh_log_common.h
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Mon Mar  4 10:07:43 2013
 *
 **/

// log mask
#define ZH_LOG_NONE    0
#define ZH_LOG_FATAL   0x01
#define ZH_LOG_WARNING 0x02
#define ZH_LOG_NOTICE  0x04
#define ZH_LOG_TRACE   0x08
#define ZH_LOG_DEBUG   0x10
#define ZH_LOG_ALL     0xff

#endif /* _ZH_LOG_COMMON_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
