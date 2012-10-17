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
 * Unittest for zh_bitops
 *
 * @file zh_bitops_SUITE.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Sun Aug 26 20:01:03 2012
 *
 **/

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include <zh_bitops.h>

#include "public.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void TEST_set_bit() {
    int d = 0;
    zh_set_bit(&d, 1);
    CU_ASSERT(d == 2);
}

void TEST_clear_bit() {
    int d = 2;
    zh_clear_bit(&d, 1);
    CU_ASSERT(d == 0);
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
        {"set_bit", suite_ptr, TEST_set_bit},
        {"clear_bit", suite_ptr, TEST_clear_bit},
    };

    size_t i;
    for (i = 0; i < sizeof(test_list) / sizeof(struct unittest); i++) {
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
