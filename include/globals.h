/****************************************************************
        GLOBAL VARIABLE DECLARATIONS
****************************************************************/
#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "cache.h"
#include "buffer.h"
#include "defs.h"

CacheEntry  g_CatCache[MAXOPEN];     /* catalog cache */
Buffer      g_Buffer[MAXOPEN];       /* buffer pool */

bool g_CacheInUse[MAXOPEN];        /* cache use bit map */
int g_CacheTimestamp[MAXOPEN];      /* The order at which they used */

char g_InvokedDirectory[MAXPATH];   /* The directory from which invoked */

int g_DBOpenFlag;                   /* Flag set to OK whenever a DB is open */

int g_PrintFlag;                    /* The error print flag */

int g_CheckDuplicateTuples;         /* Flag dictates whether duplicate tuples are allowed */

#endif
