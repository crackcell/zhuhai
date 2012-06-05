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

#define ZH_LOG_SUCC   0
#define ZH_LOG_EVENT -3
#define ZH_LOG_ERROR -4

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
    int ref_count;
    pthread_mutex_t file_lock;
    char file_name[ZH_LOG_MAX_FILE_NAME + 1];
};

struct zh_log {
    int used;
    int event_mask;
    uint64_t tid;
    char log_name[ZH_LOG_MAX_FILE_NAME];
    struct zh_log_file log_file;
    struct zh_log_file log_file_wf;
};

int zh_openlog(const char *log_path, const char *log_name,
               const int event_mask, const int log_level);
int zh_writelog(const int event, const char *format, ...);
int zh_vwritelog(struct zh_log *log_ptr, const int event, const char *format,
                 va_list args);

#endif /* _ZH_LOG_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
