/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_LOG_H_
#define _ZH_LOG_H_

/**
 * log
 *
 * @file zh_log.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 17:06:12 2012
 *
 **/

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#define ZH_LOG_MAX_FILE_SIZE 2045   /** in MB */
#define ZH_LOG_MAX_FILE_NAME 1024
#define ZH_LOG_BUFF_SIZE     2048   /** a log buff size */

#define ZH_LOG_NONE    0
#define ZH_LOG_FATAL   0x01
#define ZH_LOG_WARNING 0x02
#define ZH_LOG_NOTICE  0x04
#define ZH_LOG_TRACE   0x08
#define ZH_LOG_DEBUG   0x10
#define ZH_LOG_ALL     0xff

struct zh_log_file {
    FILE *fp;
    pthread_mutex_t lock;
    char file_name[ZH_LOG_MAX_FILE_NAME + 8]; /** + .log.wf */
};

struct zh_log {
    int used;
    int mask;
    char log_name[ZH_LOG_MAX_FILE_NAME];
    struct zh_log_file *file_ptr;
    struct zh_log_file *file_wf_ptr;
};
typedef struct zh_log * zh_log_t;

struct zh_log_unit {
    int used;
    pthread_t tid;
    int mask;
    char log_name[ZH_LOG_MAX_FILE_NAME];
    struct zh_log_file *file_ptr;
    struct zh_log_file *file_wf_ptr;
};

int zh_openlog(const char *log_name,
               const char *file_path, const char *file_name,
               const int mask);
int zh_openlog_r();

int zh_writelog(const int event, const char *format, ...);
int zh_vwritelog(const int event, const char *format, va_list args);

int zh_closelog();
int zh_closelog_r();

int zh_writelog(const int event, const char *fmt, ...);

#endif /* _ZH_LOG_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
