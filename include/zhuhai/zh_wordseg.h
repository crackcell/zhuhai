/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_WORDSEG_H_
#define _ZH_WORDSEG_H_

/**
 * 
 *
 * @file zh_wordseg.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 24 07:16:15 2012
 *
 **/

#include <scws/scws.h>
#include "zh_public.h"

typedef struct zh_wordseg {
    char dict_fullpath[PATH_MAX];
    scws_t scws;
} zh_wordseg_t;

typedef struct zh_wordseg_token {
    char *start;
    size_t len;
} zh_wordseg_token_t;

typedef struct zh_wordseg_tokenset {
    int size;
    zh_wordseg_token_t *tokens;
} zh_wordseg_tokenset_t;

zh_wordseg_t *zh_wordseg_open(const char *dict_fullpaths, size_t n,
                              const char *charset);
int zh_wordseg_close(zh_wordseg_t *p);

zh_wordseg_tokenset_t *zh_wordseg_doseg(zh_wordseg_t *p, const char *text);
void zh_wordseg_closeseg(zh_wordseg_tokenset_t *p);

#endif /* _ZH_WORDSEG_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
