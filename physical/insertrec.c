#include "../include/insertrec.h"

/**
 * Insert the record whose contents is pointed at by recPtr into relation relNum.
 *
 * @param   relNum
 * @param   recPtr
 * @return  OK or NOTOK
 */
int InsertRec(const int relNum, char*recPtr) {

    if (recPtr == NULL) {
        return ErrorMsgs(NULL_ARGUMENT_RECEIVED, g_PrintFlag);
    }

    /* Checking for duplicates */
    Rid *fRid, sRid = { 0, 0 };
    char *record;
    while (GetNextRec(relNum, &sRid, &fRid, &record) == OK && g_CheckDuplicateTuples == OK) {
        if (compareRecords(record, recPtr, g_CatCache[relNum].recLength) == OK) {
            return ErrorMsgs(DUPLICATE_TUPLE, g_PrintFlag);
        }
        sRid = *fRid;
        free(fRid);
    }

    Rid startRid = { 1, 0 }, foundRid;
    /* Insert record    */
    getNextFreeSlot(relNum, startRid, &foundRid);
    ReadPage(relNum, foundRid.pid);
    unsigned int recLength = g_CatCache[relNum].recLength;
    int i, j;
    int offset = (foundRid.slotnum - 1) * recLength;
    for (i = offset, j = 0; j < recLength; ++i, j++) {
        g_Buffer[relNum].page.contents[i] = recPtr[j];
    }

    /*  Update dirty bits and slotmap*/
    g_Buffer[relNum].dirty = TRUE;
    g_Buffer[relNum].page.slotmap = (g_Buffer[relNum].page.slotmap | 1 << (32 - foundRid.slotnum));

    /*  Update numRecs in catCache*/
    g_CatCache[relNum].dirty = TRUE;
    g_CatCache[relNum].numRecs++;
    g_CatCache[relNum].numPgs =
            g_CatCache[relNum].numPgs > foundRid.pid ? g_CatCache[relNum].numPgs : foundRid.pid;

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

    int numPgs = g_CatCache[relNum].numPgs;
    int recsPerPg = g_CatCache[relNum].recsPerPg;
    Rid prevRid, curRid = getNextRid(startRid.pid, startRid.slotnum, recsPerPg, numPgs,
            getLastRid(relNum));
    prevRid = curRid;
    int flag = NOTOK;

    while (curRid.pid <= numPgs && flag == NOTOK) {
        ReadPage(relNum, curRid.pid);
        do {
            //If slotmap says it is free
            if (!(g_Buffer[relNum].page.slotmap & (1 << (32 - curRid.slotnum)))) {
                flag = OK;
                break;
            }
            prevRid = curRid;
            curRid = getNextRid(curRid.pid, curRid.slotnum, recsPerPg, numPgs, getLastRid(relNum));
        } while (prevRid.slotnum <= curRid.slotnum);
    }
    (*foundRid) = curRid;
    return OK;
}
