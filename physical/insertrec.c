#include "../include/insertrec.h"

/**
 * Insert the record whose contents is pointed at by recPtr into relation relNum.
 *
 * @param   relNum
 * @param   recPtr
 * @return  OK or NOTOK
 */
int InsertRec(const int relNum, const char*recPtr) {

    if (recPtr == NULL) {
        return ErrorMsgs(NULL_ARGUMENT_RECEIVED, g_print_flag);
    }

    /* Checking for duplicates */
    Rid *fRid, sRid = { 0, 0 };
    char *record;
    while (GetNextRec(relNum, &sRid, &fRid, &record) == OK) {
        if (compareRecords(record, recPtr, g_catcache[relNum].recLength) == OK) {
            return ErrorMsgs(DUPLICATE_TUPLE, g_print_flag);
        }
        sRid = *fRid;
        free(fRid);
    }

    Rid startRid = { 1, 0 }, foundRid;
    /* Insert record    */
    getNextFreeSlot(relNum, startRid, &foundRid);
    unsigned int recLength = g_catcache[relNum].recLength;
    int i, j;
    int offset = (foundRid.slotnum - 1) * recLength;
    for (i = offset, j = 0; j < recLength; ++i, j++) {
        g_buffer[relNum].page.contents[i] = recPtr[j];
    }

    /*  Update dirty bits and slotmap*/
    g_buffer[relNum].dirty = TRUE;
    g_buffer[relNum].page.slotmap = (g_buffer[relNum].page.slotmap | 1 << foundRid.slotnum);

    /*  Update numRecs in catCache*/
    g_catcache[relNum].dirty = TRUE;
    g_catcache[relNum].numRecs++;
    g_catcache[relNum].numPgs = foundRid.pid;

    return OK;
}

/**
 * Gets the next free record in the relation starting from (not including) startRid
 *
 * @param   relNum
 * @param   startRid
 * @param   foundRid
 * @return  OK or NOTOK
 */
int getNextFreeSlot(const int relNum, const Rid startRid, Rid *foundRid) {

    int numPgs = g_catcache[relNum].numPgs;
    int recsPerPg = g_catcache[relNum].recsPerPg;
    Rid prevRid, curRid = getNextRid(startRid.pid, g_buffer[relNum].page.slotmap, recsPerPg, numPgs,
            getLastRid(relNum));
    prevRid = curRid;
    int flag = OK;

    while (curRid.pid <= numPgs && flag == NOTOK) {
        ReadPage(relNum, curRid.pid);
        while (prevRid.slotnum <= curRid.slotnum) {
            //If slotmap says it is free
            if (!(g_buffer[relNum].page.slotmap & (1 << curRid.slotnum))) {
                flag = OK;
                break;
            }
            prevRid = curRid;
            curRid = getNextRid(curRid.pid, g_buffer[relNum].page.slotmap, recsPerPg, numPgs,
                    getLastRid(relNum));
        }
    }
    (*foundRid) = curRid;
    return OK;
}
