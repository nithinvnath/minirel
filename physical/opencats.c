/*
 *  opencats.c
 *
 *  Created on: 30-Oct-2014
 *      Author: Dheeraj
 */


#include "../include/globals.h"
#include "../include/defs.h"
#include "../include/cache.h"
#include "../include/buffers.h"
#include "../include/globals.h"
#include "../include/readpage.h"

/*
 * Function:  OpenCats
 * ----------------------
 *  Open the system catalogs and place their entries into the catalog caches. Initialize the buffer
 *  pool control fields.
 *  
 *  returns: OK upon successful execution
 *           NOTOK otherwise
 */

int OpenCats()
{
    //printf("OpenCats \n ");

    char cat_info[8];
    int i,j;
    int num_recs_relcat;
    int num_pages_relcat;

    /* Initializing Buffer pool control fields.*/
    g_cache_in_use[0] = g_cache_in_use[1] = TRUE;
    for(i=2; i<MAXOPEN; i++)
        g_cache_in_use[i] = FALSE;

    for(i=0; i<MAXOPEN; i++){
        g_cache_timestamp[i] = 0;
        g_cache_dirty[i] = FALSE;
    }

    /* First page of relcat (RelNum = 0) */
    readpage(0,1);
    //readpage(1,2);

    strncpy(cat_info,g_buffer[0].page.contents[ DATA_OFFSET ],8);

    num_recs_relcat = bin_data[0] | bin_data[1]>>8 | bin_data[2]>>16 | bin_data[3]>>24;
    num_pages_relcat = bin_data[4] | bin_data[5]>>8 | bin_data[6]>>16 | bin_data[7]>>24;
  
    //And Add them in the correct loc and make cache[0] entry.
}