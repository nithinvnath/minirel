#include "../include/flushpage.h"

/**
 * Flush the open relation's buffer pool page. This involves writing the page to disk if it's
 * dirty, then marking the buffer page as being clean.
 *
 * @param relNum - the relation number
 * @return OK if success
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_Buffer[relNum]
 *
 * ERRORS REPORTED:
 *      RELNUM_OUT_OF_BOUND
 *      FILE_SEEK_ERROR
 *      WRITE_DISK_ERROR
 *
 * ALGORITHM:
 *      1. Check if buffer is dirty. If Not, return OK
 *      2. Construct a byte array corresponding to the page
 *      3. Seek the file to correct position and write
 *      4. Set dirty bit to false and the pid of the buffer as 0
 *
 */
int FlushPage(int relNum) {
    if (relNum < 0 || relNum >= MAXOPEN) {
        return ErrorMsgs(RELNUM_OUT_OF_BOUND, g_PrintFlag);
    }

    char slotmapbytes[4] = { 0 };
    char page[PAGESIZE] = { 0 };

    if (g_Buffer[relNum].dirty == TRUE && g_Buffer[relNum].pid != 0) {
        unsigned int slotmap = g_Buffer[relNum].page.slotmap;

        /*convert slotmap to byte array */
        convertIntToByteArray(slotmap, slotmapbytes);

        /* construct a byte array corresponding to page */
        memcpy(page, slotmapbytes, (PAGESIZE - MAXRECORD));
        memcpy(page + (PAGESIZE - MAXRECORD), g_Buffer[relNum].page.contents, MAXRECORD);

        int offset = (g_Buffer[relNum].pid - 1) * PAGESIZE;

        const int fd = g_CatCache[relNum].relFile;
        if (lseek(fd, offset, SEEK_SET) < 0) {
            return ErrorMsgs(FILE_SEEK_ERROR, g_PrintFlag);
        }
        if (write(fd, page, PAGESIZE) < 0) {
            return ErrorMsgs(WRITE_DISK_ERROR, g_PrintFlag);
        }
    }
    g_Buffer[relNum].dirty = FALSE;
    g_Buffer[relNum].pid = 0;
    g_Buffer[relNum].page.slotmap = 0;

    return OK;
}
