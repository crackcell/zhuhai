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

#include <zhuhai/zh_log.h>

TEST(zh_log_test, basic_test) {
    ASSERT_EQ(ZH_SUCC, zh_log_open("test", ".", "test_file", ZH_LOG_ALL));
    ASSERT_EQ(ZH_SUCC, zh_log_close());
}

TEST(zh_log_test, writelog) {
    ASSERT_EQ(ZH_SUCC, zh_log_open("test", ".", "test_file", ZH_LOG_ALL));
    ASSERT_EQ(ZH_SUCC, zh_log_write(ZH_LOG_DEBUG, "%s", "test log"));
    ASSERT_EQ(ZH_SUCC, zh_log_close());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
