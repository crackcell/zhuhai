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
 * @file zh_time.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 19:44:27 2012
 *
 **/

#include <zhuhai/zh_time.h>

#include <stdio.h>
#include <time.h>

char *zh_ctime(char *buff, size_t buff_size) {
    time_t t;
    struct tm tm;
    time(&t);
    localtime_r(&t, &tm);
    snprintf(buff, buff_size, "%02d-%02d %02d:%02d:%02d",
             tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return buff;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
