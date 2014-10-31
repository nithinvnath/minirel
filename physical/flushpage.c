#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/globals.h"
#include "../include/error.h"

/**
 * Flush the open relation's buffer pool page. This involves writing the page to disk if it's
 * dirty, then marking the buffer page as being clean.
 *
 * @param relNum - the relation number
 * @author nithin
 */
int FlushPage(int relNum) {
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

        const int fd = g_catcache[relNum].relFile;
        if (lseek(fd, offset, SEEK_SET) < 0) {
            ErrorMsgs(FILE_SEEK_ERROR);
            return NOTOK;
        }
        write(fd, page, PAGESIZE);
    }
    g_buffer[relNum].dirty = FALSE;
    g_buffer[relNum].pid = 0;

    return OK;
}
