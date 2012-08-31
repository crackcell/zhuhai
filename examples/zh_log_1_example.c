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
 * example for zh_log
 *
 * @file zh_log_example.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sat Sep  1 01:29:59 2012
 *
 **/

#include "zh_log.h"

#include <stdio.h>
#include <string.h>

zh_log_t g_zlog;

int main(int argc, char *argv[]) {
    zh_log_t zlog = zh_openlog("test", ".", "test_file", ZH_LOG_ALL);
    zh_writelog(ZH_LOG_DEBUG, "%s", "test log");
    zh_closelog(zlog);
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
