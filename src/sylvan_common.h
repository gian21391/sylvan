/*
 * Copyright 2011-2015 Formal Methods and Tools, University of Twente
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <cache.h>
#include <llmsset.h>
#include <refs.h>
#include <sylvan.h>
#include <tls.h>

#ifndef SYLVAN_COMMON_H
#define SYLVAN_COMMON_H

/**
 * Thread-local insert index for LLMSset
 */
extern DECLARE_THREAD_LOCAL(insert_index, uint64_t*);
uint64_t* initialize_insert_index();

/**
 * Global variables (number of workers, nodes table)
 */

extern int workers;
extern llmsset_t nodes;

/* Garbage collection test task */
TASK_DECL_0(void*, sylvan_lace_test_gc);
#define sylvan_gc_test() CALL(sylvan_lace_test_gc)

void sylvan_gc_go(int master);

/**
 * Garbage collection "mark" callbacks.
 * These are called during garbage collection to
 * recursively mark references.
 * They receive one parameter (my_id) which is the
 * index of the worker (0..workers-1)
 */
typedef void (*gc_mark_cb)(int);
void sylvan_gc_register_mark(gc_mark_cb cb);

// BDD operations
#define CACHE_ITE 0
#define CACHE_RELPROD_PAIRED 1
#define CACHE_RELPROD_PAIRED_PREV 2
#define CACHE_COUNT 3
#define CACHE_EXISTS 4
#define CACHE_SATCOUNT 5
#define CACHE_COMPOSE 6
#define CACHE_RESTRICT 7
#define CACHE_CONSTRAIN 8

// MDD operations
#define CACHE_RELPROD   10
#define CACHE_MINUS     11
#define CACHE_UNION     12
#define CACHE_INTERSECT 13
#define CACHE_PROJECT   14
#define CACHE_JOIN      15
#define CACHE_MATCH     16
#define CACHE_RELPREV   17

/**
 * Registration of quit functions
 */
typedef void (*quit_cb)();
void sylvan_register_quit(quit_cb cb);

#endif