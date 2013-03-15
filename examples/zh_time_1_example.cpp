/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2013, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_time_1_example.cpp
 * @author Menglong TAN <tanmenglong@gmail.com>
 * @date Fri Mar 15 16:19:32 2013
 *
 **/

#include <stdio.h>
#include <zhuhai/zh_time.h>

int main(int argc, char *argv[]) {
    char buff[ZH_TIME_BUFF_SIZE];
    zh_ctime(buff, sizeof(buff));
    printf("time: %s\n", buff);
    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
