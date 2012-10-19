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
 * Part of the code is from arch/x86/include/asm/bitops.h of
 * linux kernel source orginally written by Linux Torvalds
 *
 * @file zh_bitops.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Tue Oct 16 21:39:42 2012
 *
 **/

#include <stdint.h>
#include "zh_memory_barrier.h"

#ifndef LOCK_PREFIX
#define LOCK_PREFIX "\n\tlock; "
#endif

#define smp_mb__before_clear_bit()      barrier()
#define smp_mb__after_clear_bit()       barrier()

/*
 * These have to be done with inline assembly: that way the bit-setting
 * is guaranteed to be atomic. All bit operations return 0 if the bit
 * was cleared before the operation and != 0 if it was not.
 *
 * bit 0 is the LSB of addr; bit 32 is the LSB of (addr+1).
 */

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 1)
/* Technically wrong, but this avoids compilation errors on some gcc
   versions. */
#define BITOP_ADDR(x) "=m" (*(volatile long *) (x))
#else
#define BITOP_ADDR(x) "+m" (*(volatile long *) (x))
#endif

#define ADDR                            BITOP_ADDR(addr)

/*
 * We do the locked ops that don't return the old value as
 * a mask operation on a byte.
 */
#define IS_IMMEDIATE(nr)                (__builtin_constant_p(nr))
#define CONST_MASK_ADDR(nr, addr)       BITOP_ADDR((void *)(addr) + ((nr)>>3))
#define CONST_MASK(nr)                  (1 << ((nr) & 7))

/**
 * zh_atomic_set_bit - Atomically set a bit in a memory
 * @addr: the address of the memory
 * @nr: the index of the bit to set
 *
 * This function is atomic and may not be reordered.  See zh_set_bit()
 * if you do not require the atomic guarantees.
 *
 * Note: there are no guarantees that this function will not be reordered
 * on non x86 architectures, so if you are writing portable code,
 * make sure not to rely on its reordering guarantees.
 *
 * Note that @nr may be almost arbitrarily large; this function is not
 * restricted to acting on a single-word quantity.
 */
static inline void zh_atomic_set_bit(volatile void *addr, unsigned int nr) {
    if (IS_IMMEDIATE(nr)) {
        __asm__ __volatile__(
            LOCK_PREFIX "orb %[nr], %[addr]"
            : [addr] CONST_MASK_ADDR(nr, addr)
            : [nr] "iq" ((uint8_t)CONST_MASK(nr))
            : "memory");
    } else {
        __asm__ __volatile__ (
            "bts %[nr], %[addr]"
            : [addr] BITOP_ADDR(addr)
            : [nr] "Ir" (nr)
            : "memory");
    }
}

/**
 * zh_set_bit - Set a bit in memory
 * @addr: the address to start counting from
 * @nr: the bit to set
 *
 * Unlike zh_atomic_set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static inline void zh_set_bit(volatile void *addr, unsigned int nr) {
    __asm__ __volatile__(
        "bts %1,%0"
        : BITOP_ADDR(addr)
        : "Ir" (nr)
        : "memory");
}

/**
 * zh_atomic_clear_bit - Clears a bit in memory
 * @addr: Address to start counting from
 * @nr: Bit to clear
 *
 * zh_atomic_clear_bit() is atomic and may not be reordered.  However, it does
 * not contain a memory barrier, so if it is used for locking purposes,
 * you should call smp_mb__before_clear_bit() and/or smp_mb__after_clear_bit()
 * in order to ensure changes are visible on other processors.
 */
static inline void zh_atomic_clear_bit(volatile void *addr, unsigned int nr) {
    if (IS_IMMEDIATE(nr)) {
        __asm__ __volatile__(
            LOCK_PREFIX "andb %1,%0"
            : CONST_MASK_ADDR(nr, addr)
            : "iq" ((uint8_t)~CONST_MASK(nr)));
    } else {
        __asm__ __volatile__(
            LOCK_PREFIX "btr %1,%0"
            : BITOP_ADDR(addr)
            : "Ir" (nr));
    }
}

/*
 * zh_clear_bit_unlock - Clears a bit in memory
 * @addr: Address to start counting from
 * @nr: Bit to clear
 *
 * zh_clear_bit() is atomic and implies release semantics before the memory
 * operation. It can be used for an unlock.
 */
static inline void zh_clear_bit_unlock(volatile void *addr, unsigned int nr) {
    barrier();
    zh_atomic_clear_bit(addr, nr);
}

static inline void zh_clear_bit(volatile void *addr, unsigned int nr) {
    __asm__ __volatile__(
        "btr %1,%0"
        : BITOP_ADDR(addr)
        : "Ir" (nr));
}

static inline int zh_test_bit(volatile void *addr, unsigned int nr) {
    unsigned char c;
    __asm__ __volatile__(
        "bt %[p], %[a]; setb %[c]"
        : [c] "=qm" (c)
        : [a] "m" (*((size_t*)addr)), [p] "r" (nr)
        : "memory");
    return c != 0;
}

#endif /* _ZH_BITOPS_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
