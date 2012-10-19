/* -*- encoding: utf-8; indent-tabs-mode: nil -*- */

/***************************************************************
 *
 * Copyright (c) 2012, Tan Menglong <tanmenglong@gmail.com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GPL licence
 *
 **************************************************************/

#ifndef _ZH_MEMORY_BARRIER_H_
#define _ZH_MEMORY_BARRIER_H_

/**
 * Memory barrier
 * Part of the code is from arch/x86/include/asm/barrier.h in
 * linux kernel source.
 *
 * @file zh_memory_barrier.h
 * @author Tan Menglong <tanmenglong@gmail.com>
 * @date Fri Oct 19 04:35:25 2012
 *
 **/

#define barrier() __asm__ __volatile__("":::"memory")

#define mb()    __asm__ __volatile__("mfence":::"memory")
#define rmb()   __asm__ __volatile__("lfence":::"memory")
#define wmb()   __asm__ __volatile__("sfence" ::: "memory")

#endif /* _ZH_MEMORY_BARRIER_H_ */

/* vim: set expandtab shiftwidth=4 tabstop=4: */
