/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, crackcell <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_log.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 18:53:24 2012
 *
 **/

#include "zh_log.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "zh_time.h"

#define TIME_BUFF_SIZE 20

#define STRING_FATAL   "FATAL"
#define STRING_WARNING "WARNING"
#define STRING_NOTICE  "NOTICE"
#define STRING_TRACE   "TRACE"
#define STRING_DEBUG   "DEBUG"

static pthread_key_t g_log_key;

static struct zh_log *get_log();
static int zh_vwritelog_buff(struct zh_log_file *file_ptr, const char *buff);

int zh_openlog(const char *log_path, const char *log_name,
               const int event_mask, const int log_level) {
    return ZH_LOG_SUCC;
}

int zh_writelog(const int event, const char *format, ...) {
    struct zh_log *log_ptr = get_log();
    if (NULL == log_ptr) {
        return ZH_LOG_ERROR;
    }
    va_list args;
    va_start(args, format);
    int ret = zh_vwritelog(log_ptr, event, format, args);
    va_end(args);
    return ret;
}

int zh_vwritelog(struct zh_log *log_ptr, const int event,
                 const char *format, va_list args) {
    size_t bpos = 0;
    char buff[ZH_LOG_BUFF_SIZE];
    char time_buff[TIME_BUFF_SIZE];
    struct zh_log_file *file_ptr = NULL;

    buff[0] = '\0';
    time_buff[0] = '\0';

    if (log_ptr->event_mask < event || ZH_LOG_NONE == event ||
        ZH_LOG_ALL == event) {
        return ZH_LOG_EVENT;
    }

    switch(event) {
    case ZH_LOG_FATAL:
        memcpy(&buff[bpos], STRING_FATAL, sizeof(STRING_FATAL));
        file_ptr = &(log_ptr->log_file_wf);
        break;
    case ZH_LOG_WARNING:
        memcpy(&buff[bpos], STRING_WARNING, sizeof(STRING_WARNING));
        file_ptr = &(log_ptr->log_file_wf);
        break;
    case ZH_LOG_NOTICE:
        memcpy(&buff[bpos], STRING_NOTICE, sizeof(STRING_NOTICE));
        file_ptr = &(log_ptr->log_file);
        break;
    case ZH_LOG_TRACE:
        memcpy(&buff[bpos], STRING_TRACE, sizeof(STRING_TRACE));
        file_ptr = &(log_ptr->log_file);
        break;
    case ZH_LOG_DEBUG:
        memcpy(&buff[bpos], STRING_DEBUG, sizeof(STRING_DEBUG));
        file_ptr = &(log_ptr->log_file);
        break;
    default:
        break;
    }

    zh_ctime(time_buff, sizeof(time_buff));
    bpos += strnlen(&buff[bpos], ZH_LOG_BUFF_SIZE);
    bpos += snprintf(&buff[bpos], ZH_LOG_BUFF_SIZE - bpos, "%s: %s * %lu",
                     time_buff, log_ptr->log_name,
                     (unsigned long)(log_ptr->tid));
    vsnprintf(&buff[bpos], ZH_LOG_BUFF_SIZE - bpos, format, args);

    return zh_vwritelog_buff(file_ptr, buff);
}

struct zh_log *get_log() {
    return (struct zh_log*)pthread_getspecific(g_log_key);
}

int zh_vwritelog_buff(struct zh_log_file *file_ptr, const char *buff) {
    return 0;
}


/* vim: set expandtab shiftwidth=4 tabstop=4: */
