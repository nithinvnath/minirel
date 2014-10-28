/****************************************************************
        GLOBAL VARIABLE DECLARATIONS
****************************************************************/

#include "cache.h"
#include "buffer.h"

CacheEntry  g_catcache[MAXOPEN];      /* catalog cache */
Buffer      g_buffer[MAXOPEN];        /* buffer pool */
char g_db_name[RELNAME];             /* name of database */
