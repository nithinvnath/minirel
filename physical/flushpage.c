#include <string.h>
#include "../include/globals.h"
#include "../include/filewrapper.h"
#include "../include/error.h"

/**
 * Flush the open relation's buffer pool page. This involves writing the page to disk if it's
 * dirty, then marking the buffer page as being clean.
 *
 * @param relNum - the relation number
 * @author nithin
 */

//TODO Test
FlushPage(int relNum) {
    if (relNum < 0 || relNum >= MAXOPEN) {
            return RELNUM_OUT_OF_BOUND;
        }

    char slotmapbytes[4] = { 0 };
    char page[PAGESIZE] = { 0 };

    if (g_buffer[relNum].dirty == TRUE && g_buffer[relNum].pid != 0) {
        unsigned int slotmap = g_buffer[relNum].page.slotmap;

        /*convert slotmap to byte array */
        slotmapbytes[0] = slotmap & 0xFF;
        slotmapbytes[1] = (slotmap >> 8) & 0xFF;
        slotmapbytes[2] = (slotmap >> 16) & 0xFF;
        slotmapbytes[3] = (slotmap >> 24) & 0xFF;

        /* construct a byte array corresponding to page */
        memcpy(page, slotmapbytes, (PAGESIZE - MAXRECORD));
        memcpy(page + (PAGESIZE - MAXRECORD), g_buffer[relNum].page.contents, MAXRECORD);

        int offset = (g_buffer[relNum].pid - 1) * PAGESIZE;
        write_to_file(g_catcache[relNum].relName, g_db_name, offset, page, PAGESIZE);
    }
    g_buffer[relNum].dirty = FALSE;
    g_buffer[relNum].pid = 0;

    return OK;
}
