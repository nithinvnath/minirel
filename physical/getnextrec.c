#include<stdlib.h>

#include "../include/globals.h"
#include "../include/getnextrec.h"
#include "../include/readpage.h"
#include "../include/helpers.h"

/**
 * Gets the next record in sequential scan
 * @param relNum    - The relation number
 * @param startRid  - The Rid from which to begin search for next record (not including startRid).
 * @param foundRid  - The Rid of the first record after the one specified by startRid.
 * @param recPtr    - A pointer to a record-sized byte array into which the contents of the next
 *                    record (if any) will be put.
 *
 * @return flag - Found or not found
 */
int GetNextRec(const int relNum, const Rid *startRid, Rid **foundRid, char **recPtr) {
    int recsPerPg = g_catcache[relNum].recsPerPg;
    int numPgs = g_catcache[relNum].numPgs;
    int flag = NOTOK;

    Rid curRid = getNextRid(startRid->pid, startRid->slotnum, recsPerPg, numPgs,
            getLastRid(relNum));
    Rid prevRid = curRid;
    *recPtr = NULL;
    *foundRid = NULL;

    while (curRid.pid <= numPgs && flag == NOTOK) {
        if (curRid.pid == 0) { //Reached the end of records
            break;
        }
        ReadPage(relNum, curRid.pid);
        while (curRid.slotnum >= prevRid.slotnum) { //Loop till the end of cur page

            /*Check the slotmap to see if it is in use*/
            if (g_buffer[relNum].page.slotmap & (1 << (32 - curRid.slotnum))) {
                flag = OK;
                *foundRid = (Rid *) malloc(sizeof(Rid));
                (**foundRid) = curRid;
                int offset = g_catcache[relNum].recLength * (curRid.slotnum - 1);
                *recPtr = g_buffer[relNum].page.contents + offset;
                break;
            }

            prevRid = curRid;
            curRid = getNextRid(curRid.pid, curRid.slotnum, recsPerPg, numPgs, getLastRid(relNum));
            if (curRid.slotnum == 0) { //Reached the end of records in current page
                break;
            }

        }
    }
    return flag;
}

/**
 *Gets the next Rid in sequence
 *
 * @param   curPid
 * @param   curSlot
 * @param   recsPerPg
 * @param   numPgs
 * @return  the nextRid
 *          {0,0} if no next
 */

//FIXME clean this logic
Rid getNextRid(short curPid, short curSlot, int recsPerPg, int numPgs, Rid lastRid) {
    Rid nextRid = { 0, 0 };
    if (curSlot == lastRid.slotnum && curPid == lastRid.pid) { //Reached the end
        return nextRid;
    } else if (curSlot == recsPerPg) {
        nextRid.slotnum = 1;
        nextRid.pid = curPid + 1;
    } else {
        nextRid.pid = curPid == 0 ? 1 : curPid;
        nextRid.slotnum = curSlot + 1;
    }
    return nextRid;
}
