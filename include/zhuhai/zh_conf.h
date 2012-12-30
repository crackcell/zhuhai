/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_CONF_H_
#define _ZH_CONF_H_

/**
 * 
 *
 * @file zh_conf.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Dec 23 09:43:19 2012
 *
 **/

#include <stdint.h>
#include <map>
#include <string>
#include <boost/lexical_cast.hpp>

#include "zh_public.h"

typedef struct zh_conf {
    std::map<std::string, std::string> *items_ptr;
} zh_conf_t;

zh_conf_t *zh_conf_open(const char *path, const char *file);
int zh_conf_close(zh_conf_t *p);

int zh_conf_get_str(const zh_conf_t *p, const char *k, char *buff, size_t size);
int zh_conf_get_str(const zh_conf_t *p, const char *k, char *buff,
                    size_t size, const char *dft);

template <class V>
int zh_conf_get(const zh_conf_t *p, const char *k, V *v) {
    if (NULL == p || NULL == k || NULL == v) {
        return ZH_FAIL;
    }

    using namespace std;
    using namespace boost;
    map<string, string>::const_iterator pos = p->items_ptr->find(k);
    if (p->items_ptr->end() == pos) {
        return ZH_FAIL;
    }
    try {
        *v = lexical_cast<V>(pos->second);
    } catch(...) {
        return ZH_FAIL;
    }
    return ZH_SUCC;
}

template <class V>
int zh_conf_get(const zh_conf_t *p, const char *k, V *v, const V dft) {
    if (NULL == p || NULL == k || NULL == v) {
        return ZH_FAIL;
    }

    if (zh_conf_get(p, k, v) == ZH_FAIL) {
        *v = dft;
        return ZH_FAIL;
    }

    return ZH_SUCC;
}

#endif /* _ZH_CONF_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
