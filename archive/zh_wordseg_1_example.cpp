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
 * @file zh_work_1_example.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 24 10:05:38 2012
 *
 **/

#include <stdio.h>
#include <string>
#include <zhuhai/zh_wordseg.h>

using namespace std;

int main(int argc, char *argv[]) {
    zh_wordseg_t *p = zh_wordseg_open("./zh_CN-UTF8.dict", 2, "utf-8");
    if (NULL == p) {
        return 1;
    }

    const char *text = "我住在北京，我毕业于武汉大学。";

    zh_wordseg_tokenset_t *tokenset = zh_wordseg_doseg(p, text);
    printf("text:%s\ntoken count:%d\n", text, tokenset->size);
    for (int i = 0; i < tokenset->size; i++) {
        string s(tokenset->tokens[i].start, tokenset->tokens[i].len);
        printf("%s\n", s.c_str());
    }
    zh_wordseg_closeseg(tokenset);

    zh_wordseg_close(p);

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
