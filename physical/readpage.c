#include <string.h>
#include "../include/globals.h"
#include "../include/error.h"
#include "../include/filewrapper.h"
#include "../include/readpage.h"
#include "../include/flushpage.h"

/**
 * Read page pid of the open relation specified by relNum
 * and place the resulting PAGESIZE bytes in the
 * open relation's buffer slot.
 *
 * @param relNum - Relation number
 * @param pid -Page identifier
 * @author nithin
 */

//TODO Test
int ReadPage(int relNum, short pid) {
    if (relNum < 0 || relNum >= MAXOPEN) {
        return RELNUM_OUT_OF_BOUND;
    }

    if (g_buffer[relNum].pid != pid) {
        FlushPage(relNum);

        /* Calculating the offset */
        int offset = (pid - 1) * PAGESIZE;
        char page[PAGESIZE];

        read_from_file(g_catcache[relNum], g_db_name, offset, page, PAGESIZE);

        /*Copy the contents of page to buffer*/
        g_buffer[relNum].page.slotmap = page[0] | page[1] << 8 | page[2] << 16 | page[3] << 24;
        memcpy(g_buffer[relNum].page.contents, PAGESIZE - MAXRECORD, MAXRECORD);

        /* set the dirty bits and pid */
        g_buffer[relNum].pid = pid;
        g_buffer[relNum].dirty = FALSE;

    }
    return OK;
}

