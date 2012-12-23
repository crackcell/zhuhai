/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * 
 *
 * @file zh_conf_1_example.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 10:16:58 2012
 *
 **/

#include <stdio.h>
#include <string>
#include <zhuhai/zh_conf.h>

using namespace std;

int main(int argc, char *argv[]) {
    zh_conf_t *p = zh_conf_open("./", "zh_conf_1_example.conf");
    if (NULL == p) {
        return 1;
    }

    int a;
    zh_conf_get(p, "a", &a);
    printf("a=%d\n", a);

    double b;
    zh_conf_get(p, "b", &b);
    printf("b=%f\n", b);

    string c;
    zh_conf_get(p, "c", &c);
    printf("c=%s\n", c.c_str());

    zh_conf_close(p);

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
