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
#include <gtest/gtest.h>

#include <zhuhai/zh_public.h>

TEST(zh_public_test, trim_left) {
    char b[] = "   test";
    ASSERT_EQ(ZH_SUCC, zh_trim_left(b, sizeof(b)));
    ASSERT_EQ(0, strcmp(b, "test"));

    char b2[] = "  test ";
    ASSERT_EQ(ZH_SUCC, zh_trim_left(b2, sizeof(b2)));
    ASSERT_EQ(0, strcmp(b2, "test "));

    char b3[] = "";
    ASSERT_EQ(ZH_SUCC, zh_trim_left(b3, sizeof(b3)));
    ASSERT_EQ(0, strcmp(b3, ""));

    char b4[] = "test ";
    ASSERT_EQ(ZH_SUCC, zh_trim_left(b4, sizeof(b4)));
    ASSERT_EQ(0, strcmp(b4, "test "));
}

TEST(zh_public_test, trim_right) {
    char b[] = "test  ";
    ASSERT_EQ(ZH_SUCC, zh_trim_right(b, sizeof(b)));
    ASSERT_EQ(0, strcmp(b, "test"));

    char b2[] = "  test ";
    ASSERT_EQ(ZH_SUCC, zh_trim_right(b2, sizeof(b2)));
    ASSERT_EQ(0, strcmp(b2, "  test"));

    char b3[] = "";
    ASSERT_EQ(ZH_SUCC, zh_trim_right(b3, sizeof(b3)));
    ASSERT_EQ(0, strcmp(b3, ""));

    char b4[] = " test";
    ASSERT_EQ(ZH_SUCC, zh_trim_right(b4, sizeof(b4)));
    ASSERT_EQ(0, strcmp(b4, " test"));
}

TEST(zh_public_test, trim) {
    char b[] = "test  ";
    ASSERT_EQ(ZH_SUCC, zh_trim(b, sizeof(b)));
    ASSERT_EQ(0, strcmp(b, "test"));

    char b2[] = "  test ";
    ASSERT_EQ(ZH_SUCC, zh_trim(b2, sizeof(b2)));
    ASSERT_EQ(0, strcmp(b2, "test"));

    char b3[] = "";
    ASSERT_EQ(ZH_SUCC, zh_trim(b3, sizeof(b3)));
    ASSERT_EQ(0, strcmp(b3, ""));
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
