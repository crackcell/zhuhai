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
#define STRING_NONE    "NONE"

static pthread_key_t g_log_unit_key;
static pthread_once_t g_log_unit_key_once = PTHREAD_ONCE_INIT;

static int g_mask;
static char g_log_name[ZH_LOG_MAX_FILE_NAME];
static struct zh_log_file *g_file_ptr;
static struct zh_log_file *g_file_wf_ptr;

static void create_thread_key();

static inline int __openlog(const char *file_path, const char *file_name,
                            const int mask);
static inline int __openlog_file(const char *file_path, const char *file_name);
static void log_unit_destructor(void *unit_ptr);
static int __closelog_file();

static int __vwritelog(struct zh_log_unit *unit_ptr, const int event,
                       const char *fmt, va_list args);
static int __vwritelog_buff(struct zh_log_file *file_ptr, const char *buff);

int zh_openlog(const char *log_name,
               const char *file_path, const char *file_name,
               const int mask) {

    snprintf(g_log_name, sizeof(g_log_name), "%s", log_name);
    g_log_name[ZH_LOG_MAX_FILE_NAME - 1] = '\0';

    if (ZH_FAIL == __openlog_file(file_path, file_name)) {
        fprintf(stderr, "open file fail\n");
        goto error;
    }

    g_mask = mask;
    if (ZH_FAIL == zh_openlog_r()) {
        fprintf(stderr, "alloc log unit fail\n");
        goto error;
    }

    return ZH_SUCC;
error:
    return ZH_FAIL;
}

int zh_openlog_r() {

    pthread_once(&g_log_unit_key_once, create_thread_key);

    struct zh_log_unit *unit_ptr =
            (struct zh_log_unit*)malloc(sizeof(struct zh_log_unit));
    if (NULL == unit_ptr) {
        fprintf(stderr, "alloc log unit fail\n");
        goto error;
    }

    unit_ptr->mask = g_mask;
    unit_ptr->tid = pthread_self();
    unit_ptr->file_ptr = g_file_ptr;
    unit_ptr->file_wf_ptr = g_file_wf_ptr;
    snprintf(unit_ptr->log_name, sizeof(unit_ptr->log_name), "%s", g_log_name);
    unit_ptr->log_name[ZH_LOG_MAX_FILE_NAME - 1] = '\0';

    pthread_setspecific(g_log_unit_key, unit_ptr);
    unit_ptr->used = 1;

    return ZH_SUCC;
error:
    return ZH_FAIL;
}

int zh_closelog() {

    if (ZH_FAIL == __closelog_file()) {
        fprintf(stderr, "close log file fail\n");
    }

    if (ZH_FAIL == zh_closelog_r()) {
        fprintf(stderr, "close log unit fail\n");
    }

    return ZH_SUCC;
}

int zh_closelog_r() {

    // in case key has not been created
    pthread_once(&g_log_unit_key_once, create_thread_key);

    struct zh_log_unit *unit_ptr =
            (struct zh_log_unit*)pthread_getspecific(g_log_unit_key);
    if (NULL == unit_ptr) {
        fprintf(stderr, "close log unit fail: null\n");
        return ZH_FAIL;
    }
    free(unit_ptr);
    pthread_setspecific(g_log_unit_key, NULL);

    return ZH_SUCC;
}

int zh_writelog(const int event, const char *fmt, ...) {
    int ret;
    va_list args;
    va_start(args, fmt);

    struct zh_log_unit *unit_ptr =
            (struct zh_log_unit*)pthread_getspecific(g_log_unit_key);
    if (NULL == unit_ptr) {
        vfprintf(stderr, fmt, args);
        va_end(args);
        return ZH_SUCC;
    }

    ret = __vwritelog(unit_ptr, event, fmt, args);
    va_end(args);

    return ret;
}

/**********************/
/*  Private functions */
/**********************/

void create_thread_key() {
    pthread_key_create(&g_log_unit_key, log_unit_destructor);
}

void log_unit_destructor(void *unit_ptr) {
    if (unit_ptr != NULL) {
        free(unit_ptr);
    }
}

int __openlog_file(const char *file_path, const char *file_name) {
    g_file_ptr = (struct zh_log_file*)malloc(sizeof(struct zh_log));
    g_file_wf_ptr = (struct zh_log_file*)malloc(sizeof(struct zh_log));

    if (NULL == g_file_ptr || NULL == g_file_wf_ptr) {
        fprintf(stderr, "alloc log file fail\n");
        goto error;
    }

    snprintf(g_file_ptr->file_name,
             sizeof(g_file_ptr->file_name), "%s/%s.log",
             file_path, file_name);
    g_file_ptr->fp = fopen(g_file_ptr->file_name, "a+");
    if (NULL == g_file_ptr->fp) {
        goto error;
    }

    snprintf(g_file_wf_ptr->file_name,
             sizeof(g_file_wf_ptr->file_name), "%s/%s.log.wf",
             file_path, file_name);
    g_file_wf_ptr->fp = fopen(g_file_wf_ptr->file_name, "a+");
    if (NULL == g_file_wf_ptr->fp) {
        goto error;
    }

    return ZH_SUCC;
error:
    if (g_file_ptr != NULL) {
        if (g_file_ptr->fp !=0) {
            fclose(g_file_ptr->fp);
            g_file_ptr->fp = 0;
        }
        free(g_file_ptr);
        g_file_ptr = NULL;
    }
    if (g_file_wf_ptr != NULL) {
        if (g_file_wf_ptr->fp != 0) {
            fclose(g_file_wf_ptr->fp);
            g_file_wf_ptr->fp = 0;
        }
        free(g_file_wf_ptr);
        g_file_wf_ptr = NULL;
    }
    return ZH_FAIL;
}

int __closelog_file() {
    if (g_file_ptr != NULL) {
        if (g_file_ptr->fp != NULL) {
            fclose(g_file_ptr->fp);
        }
        free(g_file_ptr);
        g_file_ptr = NULL;
    }
    if (g_file_wf_ptr != NULL) {
        if (g_file_wf_ptr->fp != NULL) {
            fclose(g_file_wf_ptr->fp);
        }
        free(g_file_wf_ptr);
        g_file_wf_ptr = NULL;
    }
    return ZH_SUCC;
}

int __vwritelog(struct zh_log_unit *unit_ptr, const int event,
                const char *fmt, va_list args) {
    size_t bpos = 0;
    char buff[ZH_LOG_BUFF_SIZE];
    char time_buff[TIME_BUFF_SIZE];
    struct zh_log_file *file_ptr = NULL;

    buff[0] = '\0';
    time_buff[0] = '\0';

    if (unit_ptr->mask < event) {
        return ZH_FAIL;
    }

    if ((unit_ptr->mask & event) == 0) {
        return ZH_SUCC;
    }

    switch (event) {
    case ZH_LOG_FATAL:
        memcpy(&buff[bpos], STRING_FATAL, sizeof(STRING_FATAL));
        file_ptr = unit_ptr->file_wf_ptr;
        break;
    case ZH_LOG_WARNING:
        memcpy(&buff[bpos], STRING_WARNING, sizeof(STRING_WARNING));
        file_ptr = unit_ptr->file_wf_ptr;
        break;
    case ZH_LOG_NOTICE:
        memcpy(&buff[bpos], STRING_NOTICE, sizeof(STRING_NOTICE));
        file_ptr = unit_ptr->file_ptr;
        break;
    case ZH_LOG_TRACE:
        memcpy(&buff[bpos], STRING_TRACE, sizeof(STRING_TRACE));
        file_ptr = unit_ptr->file_ptr;
        break;
    case ZH_LOG_DEBUG:
        memcpy(&buff[bpos], STRING_DEBUG, sizeof(STRING_DEBUG));
        file_ptr = unit_ptr->file_ptr;
        break;
    default:
        memcpy(&buff[bpos], STRING_NONE, sizeof(STRING_NONE));
        file_ptr = unit_ptr->file_ptr;
        break;
    }

    zh_ctime(time_buff, sizeof(time_buff));
    bpos += strlen(&buff[bpos]);
    bpos += snprintf(&buff[bpos], sizeof(buff) - bpos, " %s: %s * %lu ",
                     time_buff, unit_ptr->log_name, unit_ptr->tid);

    vsnprintf(&buff[bpos], sizeof(buff) - bpos, fmt, args);

    return __vwritelog_buff(file_ptr, buff);
}

int __vwritelog_buff(struct zh_log_file *file_ptr, const char *buff) {
    pthread_mutex_lock(&(file_ptr->lock));
    fprintf(file_ptr->fp, "%s\n", buff);
    fflush(file_ptr->fp);
    pthread_mutex_unlock(&(file_ptr->lock));
    return ZH_SUCC;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
