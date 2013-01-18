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
 * @file zh_error.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Oct 15 11:38:44 2012
 *
 **/

#include <zhuhai/zh_error.h>

static const char* g_errorstr[] = {
    "Success",           // 0
    "General failure",   // 1
    "Invalid parameters",
    "Unknown error"      // ZH_RETCODE_NUM
};

const char *zh_strerror(int errnum) {
    if (errnum < 0 || errnum >= ZH_RETCODE_NUM) {
        return g_errorstr[ZH_RETCODE_NUM];
    }
    return g_errorstr[errnum];
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
