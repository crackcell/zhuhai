/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, crackcell <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

/**
 * Unittest for zh_log
 *
 * @file zh_log_SUITE.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 20:01:03 2012
 *
 **/

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include <zh_log.h>
#include <zh_public.h>

#include "public.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void TEST_openlog(void) {
    CU_ASSERT(zh_openlog("test", ".", "test_file", ZH_LOG_ALL) != ZH_FAIL);
}

void TEST_closelog(void) {
    CU_ASSERT(zh_closelog() != ZH_FAIL);
}

void TEST_writelog(void) {
    CU_ASSERT(zh_writelog(ZH_LOG_DEBUG, "%s", "test log"));
}

int main(int argc, char *argv[]) {
    CU_pSuite suite_ptr = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    suite_ptr = CU_add_suite("suite", init_suite, clean_suite);
    if (NULL == suite_ptr) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    struct unittest test_list[] = {
        {"openlog", suite_ptr, TEST_openlog},
        {"writelog", suite_ptr, TEST_writelog},
        {"closelog", suite_ptr, TEST_closelog},
    };

    for (size_t i = 0; i < sizeof(test_list) / sizeof(struct unittest); i++) {
        if (NULL == CU_add_test(test_list[i].suite_ptr,
                                test_list[i].test_name,
                                test_list[i].test_func)) {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
