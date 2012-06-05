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
 * log
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

#include "zh_public.h"
#include "zh_time.h"

#define TIME_BUFF_SIZE 20

#define STRING_FATAL   "FATAL"
#define STRING_WARNING "WARNING"
#define STRING_NOTICE  "NOTICE"
#define STRING_TRACE   "TRACE"
#define STRING_DEBUG   "DEBUG"

static char g_log_path[ZH_LOG_MAX_FILE_NAME + 1];
static char g_log_name[ZH_LOG_MAX_FILE_NAME + 1];

static pthread_key_t g_log_key;
static pthread_once_t g_log_key_once = PTHREAD_ONCE_INIT;

static void create_thread_key();
static int create_thread_key_once();
static struct zh_log *get_log();

static int zh_openlog_ex(struct zh_log *log_ptr, const char *file_path,
                         const char *file_name, const int mask);
static int zh_vwritelog_buff(struct zh_log_file *file_ptr, const char *buff);

int zh_openlog(const char *log_name, const char *log_path,
               const int event_mask, const int log_level) {
    struct zh_log *log_ptr = NULL;

    if (NULL == log_name || '\0' == log_name[0]) {
        snprintf(g_log_name, sizeof(g_log_name), "%s", "null");
    } else {
        strncpy(g_log_name, log_name, ZH_LOG_MAX_FILE_NAME);
        g_log_name[ZH_LOG_MAX_FILE_NAME] = '\0';
    }

    if (NULL == log_path || '\0' == log_path[0]) {
        snprintf(g_log_path, sizeof(g_log_path), "%s", ".");
    } else {
        strncpy(g_log_path, log_path, ZH_LOG_MAX_FILE_NAME);
        g_log_path[ZH_LOG_MAX_FILE_NAME] = '\0';
    }

    create_thread_key_once();

    log_ptr = (struct zh_log*)malloc(sizeof(struct zh_log));
    if (NULL == log_ptr) {
        fprintf(stderr, "no space\n");
        return ZH_FAIL;
    }

    if (ZH_SUCC != zh_openlog_ex(log_ptr, log_path, log_name, event_mask)) {
        fprintf(stderr, "zh_openlog_ex fail\n");
        goto error;
    }

    return ZH_SUCC;
error:
    if (log_ptr != NULL) {
        free(log_ptr);
        log_ptr = NULL;
    }
    return ZH_FAIL;
}

int zh_writelog(const int event, const char *format, ...) {
    struct zh_log *log_ptr = get_log();
    if (NULL == log_ptr) {
        return ZH_FAIL;
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
        return ZH_FAIL;
    }

    switch(event) {
    case ZH_LOG_FATAL:
        memcpy(&buff[bpos], STRING_FATAL, sizeof(STRING_FATAL));
        file_ptr = log_ptr->file_wf_ptr;
        break;
    case ZH_LOG_WARNING:
        memcpy(&buff[bpos], STRING_WARNING, sizeof(STRING_WARNING));
        file_ptr = log_ptr->file_wf_ptr;
        break;
    case ZH_LOG_NOTICE:
        memcpy(&buff[bpos], STRING_NOTICE, sizeof(STRING_NOTICE));
        file_ptr = log_ptr->file_ptr;
        break;
    case ZH_LOG_TRACE:
        memcpy(&buff[bpos], STRING_TRACE, sizeof(STRING_TRACE));
        file_ptr = log_ptr->file_ptr;
        break;
    case ZH_LOG_DEBUG:
        memcpy(&buff[bpos], STRING_DEBUG, sizeof(STRING_DEBUG));
        file_ptr = log_ptr->file_ptr;
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

void create_thread_key() {
    pthread_key_create(&g_log_key, NULL);
}

int create_thread_key_once() {
    pthread_once(&g_log_key_once, create_thread_key);
    return 0;
}

struct zh_log *get_log() {
    return (struct zh_log*)pthread_getspecific(g_log_key);
}

FILE *zh_openfile(const char *file_path) {
    return fopen(file_path, "a+");
}

int zh_openlog_ex(struct zh_log *log_ptr, const char *file_path,
                  const char *file_name, const int mask) {
    char tmp_buff[ZH_LOG_MAX_FILE_NAME + 8]; // filename + ".log.wf" + '\0'
    log_ptr->event_mask = mask;

    log_ptr->file_ptr = (struct zh_log_file*)malloc(sizeof(struct zh_log));
    log_ptr->file_wf_ptr = (struct zh_log_file*)malloc(sizeof(struct zh_log));

    if (NULL == log_ptr->file_ptr || NULL == log_ptr->file_wf_ptr) {
        goto error;
    }

    snprintf(tmp_buff, sizeof(tmp_buff), "%s/%s.log", file_path, file_name);
    log_ptr->file_ptr->fp = zh_openfile(tmp_buff);
    if (NULL == log_ptr->file_ptr->fp) {
        goto error;
    }

    snprintf(tmp_buff, sizeof(tmp_buff), "%s/%s.log.wf", file_path, file_name);
    log_ptr->file_wf_ptr->fp = zh_openfile(tmp_buff);
    if (NULL == log_ptr->file_wf_ptr->fp) {
        goto error;
    }

error:
    if (log_ptr->file_ptr != NULL) {
        free(log_ptr->file_ptr);
        log_ptr->file_ptr = NULL;
    }
    if (log_ptr->file_wf_ptr != NULL) {
        free(log_ptr->file_wf_ptr);
        log_ptr->file_wf_ptr = NULL;
    }
    return ZH_FAIL;
}

int zh_vwritelog_buff(struct zh_log_file *file_ptr, const char *buff) {
    return 0;
}


/* vim: set expandtab shiftwidth=4 tabstop=4: */
