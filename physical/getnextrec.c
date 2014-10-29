#include "../include/globals.h"

#define FOUND 1
#define NOT_FOUND 0

/**
 * Gets the next record in sequential scan
 * @param relNum
 * @param startRid
 * @param foundRid
 * @param recPtr
 */
int GetNextRec(int relNum, Rid *startRid, Rid *foundRid, char *recPtr) {
    int recsPerPg = g_catcache[relNum].recsPerPg;
    int numPgs = g_catcache[relNum].numPgs;
    int flag = NOT_FOUND;

    Rid curRid = getNextRid(startRid->pid, startRid->slotnum, recsPerPg);

    while (curRid.pid <= numPgs && flag==NOT_FOUND) {
        ReadPage(relNum, curRid.pid);
        while (curRid.slotnum <= recsPerPg) {
            //Check the slotmap to see if it is in use
            if (g_buffer[relNum].page.slotmap & (1 << curRid.slotnum)) {
                flag = FOUND;
                int offset = g_catcache[relNum].recLength * (curRid.slotnum-1);
                recPtr = g_buffer[relNum].page.contents + offset;
                break;
            }
            curRid = getNextRid(curRid->pid, curRid->slotnum, recsPerPg);
        }
    }
    return flag;

}

Rid getNextRid(short curPid, short curSlot, int recsPerPg) {
    Rid nextRid = { 0, 0 };
    nextRid.slotnum = (curSlot + 1) % recsPerPg;
    nextRid.pid = (nextRid.slotnum == 0) ? curPid + 1 : curPid;
    return nextRid;
}

int checkSlot(unsigned int slotmap, short slotnum) {
    int mask = 1 << slotnum;
    return slotmap & mask;
}
