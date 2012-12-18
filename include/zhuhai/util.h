/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZHUHAI_UTIL_H_
#define _ZHUHAI_UTIL_H_

/**
 * 
 *
 * @file util.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Mon Dec 17 22:21:05 2012
 *
 **/

#include <iostream>
#include <iterator>
#include <map>

namespace zhuhai {

    template <class T, class I>
    void print(const T &c, I begin, I end,
               const char *text = NULL, const char *element_spearator = " ") {
        using namespace std;
        const char *text_sparator = ": ";
        if (text) {
            cout << text << text_sparator;
        }

        copy(begin, end,
             ostream_iterator<typename T::value_type>(cout, element_spearator));
        cout << endl;
    }

    template <class T>
    void print(const T &c, const char *text = NULL,
               const char *element_spearator = " ") {
        print(c, c.begin(), c.end(), text, element_spearator);
    }

}

#endif /* _ZHUHAI_UTIL_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
