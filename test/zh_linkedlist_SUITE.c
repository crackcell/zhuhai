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
#include <malloc.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <zh_linkedlist.h>

#include "public.h"

struct node {
    zh_linkedlist_node_t __node;
    int val;
};

zh_linkedlist_t g_list;

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void TEST_init(void) {
    CU_ASSERT(zh_linkedlist_init(&g_list) != ZH_FAIL);
}

void TEST_clear(void) {
    CU_ASSERT(zh_linkedlist_clear(&g_list) != ZH_FAIL);
}

void TEST_push_back(void) {
    int i;
    struct node *n;
    for (i = 0; i < 10; i++) {
        n = (struct node*)malloc(sizeof(struct node));
        n->val = i;
        CU_ASSERT(zh_linkedlist_push_back(&g_list, n)  != ZH_FAIL);
    }
    for (i = 0; i < 10; i++) {
        n = (struct node*)zh_linkedlist_at(&g_list, i);
        CU_ASSERT(n->val == i);
    }
}

void TEST_push_front(void) {
    int i;
    struct node *n;
    for (i = 0; i < 10; i++) {
        n = (struct node*)malloc(sizeof(struct node));
        n->val = i;
        CU_ASSERT(zh_linkedlist_push_front(&g_list, n)  != ZH_FAIL);
    }
    for (i = 9; i <= 0; i--) {
        n = (struct node*)zh_linkedlist_at(&g_list, i);
        CU_ASSERT(n->val == i);
    }
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
        {"init", suite_ptr, TEST_init},
        {"push_back", suite_ptr, TEST_push_back},
        {"push_front", suite_ptr, TEST_push_front},
        {"clear", suite_ptr, TEST_clear},
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
