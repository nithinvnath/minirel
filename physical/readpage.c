#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/globals.h"
#include "../include/error.h"
#include "../include/readpage.h"
#include "../include/flushpage.h"
#include "../include/readpage.h"
#include "../include/helpers.h"

/**
 * Read page pid of the open relation specified by relNum
 * and place the resulting PAGESIZE bytes in the
 * open relation's buffer slot.
 *
 * @param relNum - Relation number
 * @param pid -Page identifier
 * @author nithin
 */
int ReadPage(int relNum, short pid) {
    if (relNum < 0 || relNum >= MAXOPEN) {
        return RELNUM_OUT_OF_BOUND;
    }

    if (g_buffer[relNum].pid != pid) {
        FlushPage(relNum);

        /* Calculating the offset */
        int offset = (pid - 1) * PAGESIZE;
        char page[PAGESIZE];

        /*Seek in file */
        const int fd = g_catcache[relNum].relFile;
        if (lseek(fd, offset, SEEK_SET) < 0) {
            return NOTOK;
        }
        read(fd, page, PAGESIZE); //Read Page

        /*Copy the contents of page to buffer*/
        g_buffer[relNum].page.slotmap = readIntFromByteArray(page, 0);
        memcpy(g_buffer[relNum].page.contents, page + (PAGESIZE - MAXRECORD), MAXRECORD);

        /* set the dirty bits and pid */
        g_buffer[relNum].pid = pid;
        g_buffer[relNum].dirty = FALSE;

    }
    return OK;
}

