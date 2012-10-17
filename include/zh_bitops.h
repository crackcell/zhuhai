/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_BITOPS_H_
#define _ZH_BITOPS_H_

/**
 * Bit operations
 *
 * @file zh_bitops.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Tue Oct 16 21:39:42 2012
 *
 **/

#define LOCK "lock ; "

static inline void zh_set_bit(volatile void *addr, const int nr) {
    __asm__ __volatile__  ("bts %1, %0"
             : "=m" (*((size_t*)addr))
             : "Ir" (nr)
             : "memory");
}

static inline void zh_clear_bit(volatile void *addr, const int nr) {
    __asm__ __volatile__  ("btr %1, %0"
             : "=m" (*((size_t*)addr))
             : "Ir" (nr)
             : "memory");
}

#endif /* _ZH_BITOPS_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
