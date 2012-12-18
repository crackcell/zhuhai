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
 * @file zh_util_test.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 17 23:46:48 2012
 *
 **/

#include <zhuhai/util.h>
#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

TEST(PrintTest, Vector) {
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    zhuhai::print(v);
}

TEST(PrintTest, VectorWithIterator) {
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    zhuhai::print(v, v.begin(), v.end());
}

TEST(PrintTest, VectorWithReverseIterator) {
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    zhuhai::print(v, v.rbegin(), v.rend());
}

/*
TEST(PrintTest, Map) {
    map<string, int> m;
    m["0"] = 0;
    m["1"] = 1;
    m["2"] = 2;
    m["3"] = 3;
    m["4"] = 4;
    zhuhai::print(m);
}
*/

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
