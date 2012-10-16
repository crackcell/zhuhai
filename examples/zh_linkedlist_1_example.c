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
 * 
 *
 * @file zh_linkedlist_1_example.c
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Tue Oct 16 11:26:36 2012
 *
 **/

#include <stdio.h>
#include <zh_linkedlist.h>

struct node {
    zh_linkedlist_node_t __node;
    int val;
};

int main(int argc, char *argv[]) {
    zh_linkedlist_t l;

    zh_linkedlist_init(&l);

    int i;
    for (i = 0; i < 10; i++) {
        struct node n;
        n.val = i;
        zh_linkedlist_push_back(&l, &n);
    }
    printf("%d\n", l.size);
    for (i = 0; i < 10; i++) {
        struct node n;
        n.val = i;
        zh_linkedlist_push_front(&l, &n);
    }
    printf("%d\n", l.size);

    zh_linkedlist_clear(&l);

    return 0;
}

/* vim: set expandtab shiftwidth=4 tabstop=4: */
