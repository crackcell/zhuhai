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
 * Unittest for zh_atomic
 *
 * @file zh_atomic_SUITE.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Oct 18 10:45:54 2012
 *
 **/

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <zh_atomic.h>

#include "public.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void TEST_set() {
    zh_atomic_t a;
    zh_atomic_set(&a, 12);
    CU_ASSERT(zh_atomic_get(&a) == 12);
}

void TEST_add() {
    zh_atomic_t a;
    zh_atomic_set(&a, 12);
    zh_atomic_add(&a, 10);
    CU_ASSERT(zh_atomic_get(&a) == 22);
}

void TEST_sub() {
    zh_atomic_t a;
    zh_atomic_set(&a, 12);
    zh_atomic_sub(&a, 10);
    CU_ASSERT(zh_atomic_get(&a) == 2);
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
        {"set", suite_ptr, TEST_set},
        {"add", suite_ptr, TEST_add},
        {"sub", suite_ptr, TEST_sub},
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
