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
char g_db_name[RELNAME];             /* name of database */
bool g_cache_in_use[MAXOPEN];        /* cache use bit map */
int g_cache_timestamp[MAXOPEN];      /* The order at which they used */
bool g_cache_dirty[MAXOPEN];         /* Cache Entry is dirty or not */

#endif