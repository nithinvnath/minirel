/****************************************************************
        GLOBAL VARIABLE DECLARATIONS
****************************************************************/
#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "cache.h"
#include "buffer.h"
#include "defs.h"

CacheEntry  g_catcache[MAXOPEN];     /* catalog cache */
Buffer      g_buffer[MAXOPEN];       /* buffer pool */

bool g_cache_in_use[MAXOPEN];        /* cache use bit map */
int g_cache_timestamp[MAXOPEN];      /* The order at which they used */

char g_invoked_directory[MAXPATH];   /* The directory from which invoked */

int g_db_open_flag;

int g_print_flag;                    /* The error print flag */

int g_check_duplicate_tuples;         /* Flag dictates whether duplicate tuples are allowed */

#endif
