/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_META_H_
#define _ZH_META_H_

/**
 * 
 *
 * @file zh_meta.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 19:32:02 2012
 *
 **/

#include <string.h>
#include <zhuhai/zh_public.h>

#ifndef ZH_OBJECT_NAME_SIZE
#define ZH_OBJECT_NAME_SIZE 128
#endif

typedef struct zh_meta {
    char name[ZH_OBJECT_NAME_SIZE + 1];
} zh_meta_t;

extern const char *g_s_null_name;

zh_meta_t *zh_meta_init(const char *name);

static inline const char *zh_meta_get_name(void *p) {
    if (NULL == p) {
        return g_s_null_name;
    }

    zh_meta_t *m = (zh_meta_t*)p;

    return m->name;
}

static inline int zh_meta_set_name(void *p, const char *name) {
    if (NULL == p || NULL == name) {
        return ZH_FAIL;
    }

    zh_meta_t *m = (zh_meta_t*)p;
    bzero(m->name, sizeof(m->name));
    strncpy(m->name, name, sizeof(m->name));

    return ZH_SUCC;
}

#endif /* _ZH_META_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
