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
 * @file zh_conf.cpp
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 09:47:54 2012
 *
 **/

#include <zhuhai/zh_conf.h>

#include <stdio.h>
#include <errno.h>
#include <boost/lexical_cast.hpp>

#include <zhuhai/zh_public.h>
#include <zhuhai/zh_log.h>

using namespace std;
using namespace boost;

static int parse_line(zh_conf_t *p, char *line, size_t size) {
    char *delim = strchr(line, ':');
    if (NULL == delim) {
        return ZH_FAIL;
    }

    *delim = '\0';
    char k[ZH_LINE_BUFF_SIZE];
    char v[ZH_LINE_BUFF_SIZE];

    bzero(k, sizeof(k));
    bzero(v, sizeof(v));

    strncpy(k, line, sizeof(k));
    strncpy(v, delim + 1, sizeof(v));

    zh_trim(k, sizeof(k));
    zh_trim(v, sizeof(v));

    (*(p->items_ptr))[k] = v;

    return ZH_SUCC;
}

static int load_conf(zh_conf_t *p, FILE *f) {
    char buff[ZH_LINE_BUFF_SIZE];
    bzero(buff, sizeof(buff));
    while (fgets(buff, sizeof(buff), f)) {
        parse_line(p, buff, sizeof(buff));
    }
    return ZH_SUCC;
}

zh_conf_t *zh_conf_open(const char *path, const char *file) {
    using namespace std;

    if (NULL == path || NULL == file) {
        return NULL;
    }

    FILE *f;
    char fullpath[PATH_MAX];

    zh_conf_t *p = (zh_conf_t*)malloc(sizeof(zh_conf_t));
    if (NULL == p) {
        goto err;
    }

    p->items_ptr = new (nothrow) map<string, string>;

    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, file);
    f = fopen(fullpath, "r");
    if (NULL == f) {
        ZH_FATAL("open file fail[%s][%s]", fullpath, strerror(errno));
        goto err;
    }

    if (load_conf(p, f) == ZH_FAIL) {
        ZH_FATAL("load conf fail");
        goto err;
    }

    fclose(f);

    return p;
err:
    if (p != NULL) {
        free(p);
        p = NULL;
    }
    if (f != NULL) {
        fclose(f);
        f = NULL;
    }
    return NULL;
}

int zh_conf_close(zh_conf_t *p) {
    if (NULL == p) {
        return ZH_FAIL;
    }

    if (p->items_ptr != NULL) {
        delete p->items_ptr;
    }

    free(p);

    return ZH_SUCC;
}

int zh_conf_get_str(const zh_conf_t *p, const char *k, char *buff,
                    size_t size) {
    if (NULL == p || NULL == k || NULL == buff) {
        return ZH_FAIL;
    }

    using namespace std;
    map<string, string>::const_iterator pos = p->items_ptr->find(k);
    if (p->items_ptr->end() == pos) {
        return ZH_FAIL;
    }
    strncpy(buff, pos->second.c_str(), size);

    return ZH_SUCC;
}

int zh_conf_get_str(const zh_conf_t *p, const char *k, char *buff,
                    size_t size, const char *dft) {
    if (NULL == p || NULL == buff || NULL == dft) {
        return ZH_FAIL;
    }

    if (zh_conf_get_str(p, k, buff, size) == ZH_FAIL) {
        strncpy(buff, dft, size);
        return ZH_FAIL;
    }

    return ZH_SUCC;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
