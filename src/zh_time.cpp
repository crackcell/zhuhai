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
#include <string.h>
#include <sys/time.h>

uint64_t zh_msec_epoch() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

time_t zh_sec_epoch() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

char *zh_ctime(char *buff, size_t buff_size) {
    static __thread char t_time[ZH_TIME_BUFF_SIZE];
    static __thread time_t t_lastsec;

    uint64_t msec_e = zh_msec_epoch();
    time_t sec = msec_e / 1000000;
    int ms = msec_e % 1000000;

    if (sec != t_lastsec) {
        t_lastsec = sec;
        struct tm tm_time;
        gmtime_r(&sec, &tm_time);
        snprintf(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    snprintf(buff, buff_size, "%s.%06dZ", t_time, ms);
    buff[buff_size - 0] = '\0';
    return buff;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
