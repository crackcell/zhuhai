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
 * Unittest for zh_log
 *
 * @file zh_log_SUITE.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 20:01:03 2012
 *
 **/

#include <stdio.h>
#include <string.h>
#include <string>
#include <gtest/gtest.h>

#include "zh_conf.h"
#include "zh_math.h"

using namespace std;

TEST(zh_conf_test, open) {
    zh_conf_t *p = zh_conf_open("./", "./zh_conf_unittest.conf");
    ASSERT_TRUE(p != NULL);
    ASSERT_EQ(ZH_SUCC, zh_conf_close(p));
}

TEST(zh_conf_test, get_int) {
    zh_conf_t *p = zh_conf_open("./", "./zh_conf_unittest.conf");
    ASSERT_TRUE(p != NULL);
    int a;
    ASSERT_TRUE(zh_conf_get(p, "a", &a) == ZH_SUCC);
    ASSERT_EQ(ZH_SUCC, zh_conf_close(p));
}

TEST(zh_conf_test, get_double) {
    zh_conf_t *p = zh_conf_open("./", "./zh_conf_unittest.conf");
    ASSERT_TRUE(p != NULL);
    double b;
    ASSERT_TRUE(zh_conf_get(p, "b", &b) == ZH_SUCC);
    ASSERT_TRUE(zh_double_cmp(b, 2.2));
    ASSERT_EQ(ZH_SUCC, zh_conf_close(p));
}

TEST(zh_conf_test, get_str) {
    zh_conf_t *p = zh_conf_open("./", "./zh_conf_unittest.conf");
    ASSERT_TRUE(p != NULL);
    string c;
    ASSERT_TRUE(zh_conf_get(p, "c", &c) == ZH_SUCC);
    ASSERT_TRUE("test" == c);
    ASSERT_EQ(ZH_SUCC, zh_conf_close(p));
}

TEST(zh_conf_test, get_cstr) {
    zh_conf_t *p = zh_conf_open("./", "./zh_conf_unittest.conf");
    ASSERT_TRUE(p != NULL);
    char buff[1024];
    ASSERT_TRUE(zh_conf_get_str(p, "c", buff, sizeof(buff)) == ZH_SUCC);
    ASSERT_TRUE(strncmp(buff, "test", sizeof(buff)) == 0);
    ASSERT_EQ(ZH_SUCC, zh_conf_close(p));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
