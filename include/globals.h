/****************************************************************
        GLOBAL VARIABLE DECLARATIONS
****************************************************************/

#include "cache.h"
#include "buffer.h"

CacheEntry  g_catcache[MAXOPEN];      /* catalog cache */
Buffer      g_buffer[MAXOPEN];        /* buffer pool */

