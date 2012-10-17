/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the BSD licence
 *
 * The code is partly rewritten from hypertable's source code
 *
 **************************************************************/

#ifndef _ZH_ATOMIC_H_
#define _ZH_ATOMIC_H_

/**
 * Atomic operations
 *
 * @file zh_atomic.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Thu Oct 18 03:27:51 2012
 *
 **/

#include "zh_public.h"

#define LOCK "lock ; "

typedef struct { volatile int counter; } zh_atomic_t;

#define zh_atomic_get(a) ((a)->counter)

#define zh_atomic_set(a, v) (((a)->counter) = (v))

static inline void zh_atomic_add(zh_atomic_t *a, int v) {
    __asm__ __volatile__(
        LOCK "addl %[a] %[v]"
        : [a] "=m" (a->counter)
        : [v] "ir" (v), "m" (a->counter));
}

static inline void zh_atomic_sub(zh_atomic_t *a, int v) {}

static inline int zh_atomic_add_return(zh_atomic_t *a, int v) {
    int k;
    k = v;
    __asm__ __volatile__(
        LOCK "xaddl %[v], %[a]"
        : [v] "+r" (v), [a] "+m" (a->counter)
        : : "memory");
    return v + k;
}

static inline int zh_atomic_sub_return(zh_atomic_t *a, int v) {return 0;}

static inline int zh_atomic_add_and_test(zh_atomic_t *a, int v) {return 0;}

static inline void zh_atomic_inc(zh_atomic_t *a) {
    __asm__ __volatile__(
        LOCK "incl %[a]"
        : [a] "=m" (a->counter)
        : "m" (a->counter));
}

static inline void zh_atomic_dec(zh_atomic_t *a) {}

static inline int zh_atomic_dec_and_test(zh_atomic_t *a, int v) {return 0;}

static inline int zh_atomic_inc_and_test(zh_atomic_t *a, int v) {return 0;}

static inline int zh_atomic_add_and_negative(zh_atomic_t *a, int v) {return 0;}

#define zh_atomic_inc_return(a) (zh_atomic_add_return(a, 1))
#define zh_atomic_dec_return(a) (zh_atomic_sub_return(a, 1))

#endif /* _ZH_ATOMIC_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
