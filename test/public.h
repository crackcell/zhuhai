/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _PUBLIC_TEST_DEF_H_
#define _PUBLIC_TEST_DEF_H_

/**
 * Public definitions for testing
 *
 * @file public_test_def.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sat Jun  2 13:43:26 2012
 *
 **/

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

struct unittest {
    const char *test_name;
    CU_pSuite suite_ptr;
    void (*test_func)(void);
};

#endif /* _PUBLIC_TEST_DEF_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
