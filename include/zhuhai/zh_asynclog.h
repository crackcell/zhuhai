/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_ASYNCLOG_H_
#define _ZH_ASYNCLOG_H_

/**
 * async log
 *
 * @file zh_asynclog.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Mar  4 09:58:36 2013
 *
 **/

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include <string>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_queue.h>

#include "zh_public.h"
#include "internal/zh_log_common.h"

#define ZH_LOG_MAX_FILE_SIZE 2045   /** in MB */
#define ZH_LOG_MAX_FILE_NAME 1024
#define ZH_LOG_BUFF_SIZE     2048   /** a log buff size */

#define ZH_FATAL(fmt, arg...)                                           \
    do {                                                                \
        zh_asynclog_write(ZH_LOG_FATAL, "[%s:%s:%d]" fmt, __FILE__,     \
                     __FUNCTION__, __LINE__, ##arg);                    \
    } while(0)

#define ZH_WARN(fmt, arg...)                                            \
    do {                                                                \
        zh_asynclog_write(ZH_LOG_WARNING, "[%s:%s:%d]" fmt, __FILE__,   \
                     __FUNCTION__, __LINE__, ##arg);                    \
    } while(0)

#define ZH_NOTICE(fmt, arg...)                                          \
    do {                                                                \
        zh_asynclog_write(ZH_LOG_NOTICE, "[%s:%s:%d]" fmt, __FILE__,    \
                     __FUNCTION__, __LINE__, ##arg);                    \
    } while(0)

#define ZH_TRACE(fmt, arg...)                                           \
    do {                                                                \
        zh_asynclog_write(ZH_LOG_TRACE, "[%s:%s:%d]" fmt, __FILE__,     \
                     __FUNCTION__, __LINE__, ##arg);                    \
    } while(0)

#ifdef _DEBUG
#define ZH_DEBUG(fmt, arg...)                                           \
    do {                                                                \
        zh_asynclog_write(ZH_LOG_DEBUG, "[%s:%s:%d]" fmt, __FILE__,     \
                     __FUNCTION__, __LINE__, ##arg);                    \
    } while(0)
#else
#define ZH_DEBUG(fmt, arg...) do {} while(0)
#endif

struct zh_asynclog_file {
    FILE *fp;
    char file_name[ZH_LOG_MAX_FILE_NAME + 8]; /** + .log.wf */
};

struct zh_asynclog_frontend {
    pid_t tid;
    int mask;
    char log_name[ZH_LOG_MAX_FILE_NAME];
};

struct zh_asynclog_backend {
    tbb::concurrent_queue<std::string> *queue;
};

zh_ret_t zh_log_open(const char *log_name,
                     const char *file_path, const char *file_name,
                     const int mask);
zh_ret_t zh_log_open_r();

zh_ret_t zh_asynclog_write(const int event, const char *format, ...);

zh_ret_t zh_log_close();
zh_ret_t zh_log_close_r();

zh_ret_t zh_asynclog_write(const int event, const char *fmt, ...);

#endif /* _ZH_ASYNCLOG_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
