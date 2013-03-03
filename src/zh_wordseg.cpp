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
 * @file zh_wordseg.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 24 08:28:00 2012
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <zhuhai/zh_wordseg.h>
#include <zhuhai/zh_public.h>

using namespace std;

zh_wordseg_t *zh_wordseg_open(const char *fullpaths, size_t n,
                              const char *charset) {
    if (n <= 0 || NULL == charset) {
        return NULL;
    }

    char *paths = NULL;
    size_t paths_size;;
    char *delim, *start;

    zh_wordseg_t *w = (zh_wordseg_t*)malloc(sizeof(zh_wordseg_t));
    if (NULL == w) {
        goto err;
    }

    w->scws = scws_new();
    scws_set_charset(w->scws, charset);

    printf("%s\n", fullpaths);

    paths_size = strlen(fullpaths) + 1;
    paths = (char*)malloc(paths_size);
    bzero(paths, paths_size);
    strncpy(paths, fullpaths, paths_size);

    start = paths;
    while(1) {

        delim = strchr(paths, ':');
        if (delim != NULL) {
            *delim = '\0';
        }
        if (scws_add_dict(w->scws, start, SCWS_XDICT_XDB) < 0) {
            fprintf(stderr, "load dict fail[%s]", start);
        }
        fprintf(stderr, "load dict[%s]", start);
        if (delim != NULL) {
            start = delim + 1;
        } else {
            break;
        }

    }

    return w;
err:
    if (w != NULL) {
        scws_free(w->scws);
        free(w);
    }
    if (paths != NULL) {
        free(paths);
    }
    return NULL;
}

int zh_wordseg_close(zh_wordseg_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    scws_free(p->scws);
    free(p);

    return ZH_SUCC;
}

zh_wordseg_tokenset_t *zh_wordseg_doseg(zh_wordseg_t *p, const char *text) {
    if (NULL == p || NULL == text) {
        return NULL;
    }

    vector<zh_wordseg_token_t> tokenset;
    scws_send_text(p->scws, text, strlen(text));
    scws_res_t cur, res;
    while ((cur = res = scws_get_result(p->scws)) != NULL) {
        while (cur != NULL) {
            zh_wordseg_token_t t;
            t.start = (char*)(text + cur->off);
            t.len = cur->len;
            tokenset.push_back(t);
            cur = cur->next;
        }
    }

    size_t b;
    zh_wordseg_tokenset_t *pset =
            (zh_wordseg_tokenset_t*)malloc(sizeof(zh_wordseg_tokenset_t));
    if (NULL == pset) {
        goto err;
    }
    b = sizeof(zh_wordseg_token_t) * tokenset.size();
    pset->tokens = (zh_wordseg_token_t*)malloc(b);
    if (NULL == pset->tokens) {
        goto err;
    }
    memcpy(pset->tokens, (char*)&tokenset[0], b);
    pset->size = tokenset.size();

    return pset;
err:
    if (pset != NULL) {
        if (pset->tokens != NULL) {
            free(pset->tokens);
        }
        free(pset);
    }
    return NULL;
}

void zh_wordseg_closeseg(zh_wordseg_tokenset_t *p) {
    if (NULL == p) {
        return;
    }
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
