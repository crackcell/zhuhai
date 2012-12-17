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
#include <boost/iterator.hpp>
#include <boost/utility.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>

namespace zhuhai {
    template <class T>
    void print(const T &c, const char *text = NULL,
               const char *element_spearator = " ") {
        print(c, c.begin(), c.end(), text, element_spearator);
    }

    template <class T, class I>
    void print(const T &c, I begin, I end,
               const char *text = NULL, const char *element_spearator = " ") {
        using namespace std;
        const char *text_sparator = ": ";
        if (text) {
            cout << text << text_sparator;
        }

        typename T::const_iterator c_end = c.end();
        copy(begin, end,
             ostream_iterator<typename T::value_type>(cout, element_spearator));
        cout << endl;
    }

}

#endif /* _ZHUHAI_UTIL_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
