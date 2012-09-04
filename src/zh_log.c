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

static pthread_key_t g_log_unit_key;
static pthread_once_t g_log_unit_key_once = PTHREAD_ONCE_INIT;

static void create_thread_key();

static inline int __openlog(struct zh_log *log_ptr, const char *file_path,
                            const char *file_name, const int mask);
static inline int __openlog_file(struct zh_log *log_ptr, const char *file_path,
                                 const char *file_name);
static void log_unit_destructor(void *unit_ptr);
static inline int __openlog_unit_r(struct zh_log *log_ptr, const char *log_name);

zh_log_t zh_openlog(const char *log_name,
                    const char *file_path, const char *file_name,
                    const int event_mask) {
    struct zh_log *log_ptr = (struct zh_log*)malloc(sizeof(struct zh_log));
    if (NULL == log_ptr) {
        fprintf(stderr, "mem error\n");
        goto error;
    }
    bzero(log_ptr, sizeof(struct zh_log));

    if (ZH_FAIL == __openlog_file(log_ptr, file_path, file_name)) {
        fprintf(stderr, "open file fail\n");
        goto error;
    }

    if (ZH_FAIL == __openlog_unit_r(log_ptr, log_name)) {
        fprintf(stderr, "alloc log unit fail\n");
        goto error;
    }

    return log_ptr;
error:
    if (log_ptr != NULL) {
        free(log_ptr);
        log_ptr = NULL;
    }
    return NULL;
}

// Private functions

void create_thread_key() {
    pthread_key_create(&g_log_unit_key, log_unit_destructor);
}

void log_unit_destructor(void *unit_ptr) {
    if (unit_ptr != NULL) {
        free(unit_ptr);
    }
}

int __openlog_unit_r(struct zh_log *log_ptr, const char *log_name) {
    pthread_once(&g_log_unit_key_once, create_thread_key);

    struct zh_log_unit *unit_ptr =
            (struct zh_log_unit*)malloc(sizeof(struct zh_log_unit));
    if (NULL == unit_ptr) {
        fprintf(stderr, "alloc log unit fail\n");
        goto error;
    }
    unit_ptr->tid = pthread_self();
    unit_ptr->file_ptr = log_ptr->file_ptr;
    unit_ptr->file_wf_ptr = log_ptr->file_wf_ptr;
    snprintf(unit_ptr->log_name, sizeof(unit_ptr->log_name), "%s", log_name);
    unit_ptr->log_name[ZH_LOG_MAX_FILE_NAME - 1] = '\0';

    pthread_setspecific(g_log_unit_key, unit_ptr);

    return ZH_SUCC;
error:
    return ZH_FAIL;
}

int __openlog_file(struct zh_log *log_ptr, const char *file_path,
                   const char *file_name) {
    log_ptr->file_ptr = (struct zh_log_file*)malloc(sizeof(struct zh_log));
    log_ptr->file_wf_ptr = (struct zh_log_file*)malloc(sizeof(struct zh_log));

    if (NULL == log_ptr->file_ptr || NULL == log_ptr->file_wf_ptr) {
        fprintf(stderr, "alloc log file fail\n");
        goto error;
    }

    snprintf(log_ptr->file_ptr->file_name,
             sizeof(log_ptr->file_ptr->file_name), "%s/%s.log",
             file_path, file_name);
    log_ptr->file_ptr->fp = fopen(log_ptr->file_ptr->file_name, "a+");
    if (NULL == log_ptr->file_ptr->fp) {
        goto error;
    }

    snprintf(log_ptr->file_wf_ptr->file_name,
             sizeof(log_ptr->file_wf_ptr->file_name), "%s/%s.log.wf",
             file_path, file_name);
    log_ptr->file_wf_ptr->fp = fopen(log_ptr->file_wf_ptr->file_name, "a+");
    if (NULL == log_ptr->file_wf_ptr->fp) {
        goto error;
    }

    return ZH_SUCC;
error:
    if (log_ptr->file_ptr != NULL) {
        if (log_ptr->file_ptr->fp !=0) {
            fclose(log_ptr->file_ptr->fp);
            log_ptr->file_ptr->fp = 0;
        }
        free(log_ptr->file_ptr);
        log_ptr->file_ptr = NULL;
    }
    if (log_ptr->file_wf_ptr != NULL) {
        if (log_ptr->file_wf_ptr->fp != 0) {
            fclose(log_ptr->file_wf_ptr->fp);
            log_ptr->file_wf_ptr->fp = 0;
        }
        free(log_ptr->file_wf_ptr);
        log_ptr->file_wf_ptr = NULL;
    }
    return ZH_FAIL;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
