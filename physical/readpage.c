#include "../include/readpage.h"

/**
 * Read page pid of the open relation specified by relNum
 * and place the resulting PAGESIZE bytes in the
 * open relation's buffer slot.
 *
 * @param relNum - Relation number
 * @param pid -Page identifier
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_Buffer[relNum]
 *
 * ERRORS REPORTED:
 *      RELNUM_OUT_OF_BOUND
 *      PID_OUT_OF_BOUND
 *      READ_DISK_ERROR
 *
 * ALGORITHM:
 *      1. Check to see if the pid in buffer matches required pid. If so return
 *      2. Flush the page currently in buffer to disk. FlushPage()
 *      3. If we are trying to read a new page into buffer, simply set slotmap to 0
 *      4. Otherwise seek to appropriate file location and copy the contents to page
 *      5. Set the dirty bit and pid in buffer
 *
 * IMPLEMENTATION NOTES:
 *      Uses FlushPage()
 *
 */
int ReadPage(int relNum, short pid) {
    if (relNum < 0 || relNum >= MAXOPEN) {
        return ErrorMsgs(RELNUM_OUT_OF_BOUND, g_PrintFlag);
    }

    if (pid > (g_CatCache[relNum].numPgs + 1)) {
        return ErrorMsgs(PID_OUT_OF_BOUND, g_PrintFlag);
    }
    if (g_Buffer[relNum].pid != pid) {

        if (FlushPage(relNum) != OK) { //Flush page
            return NOTOK;
        }

        if (pid == g_CatCache[relNum].numPgs + 1) { //Trying to read a fresh page into buffer.
        //simply set the slotmap to show all records are free
            g_Buffer[relNum].page.slotmap = 0;
        } else { //Seek the file and load data into buffer
            /* Calculating the offset */
            int offset = (pid - 1) * PAGESIZE;
            char page[PAGESIZE];

            /*Seek in file */
            const int fd = g_CatCache[relNum].relFile;
            if (lseek(fd, offset, SEEK_SET) < 0) {
                return NOTOK;
            }
            if (read(fd, page, PAGESIZE) < 0) { //Read Page
                return ErrorMsgs(READ_DISK_ERROR, g_PrintFlag);
            }

            /*Copy the contents of page to buffer*/
            g_Buffer[relNum].page.slotmap = readIntFromByteArray(page, 0);
            memcpy(g_Buffer[relNum].page.contents, page + (PAGESIZE - MAXRECORD), MAXRECORD);
        }

        /* set the dirty bits and pid */
        g_Buffer[relNum].pid = pid;
        g_Buffer[relNum].dirty = FALSE;

    }
    return OK;
}

