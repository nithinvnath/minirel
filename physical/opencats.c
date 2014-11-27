/*
 * opencats.c
 *
 *  Created on: 30-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/opencats.h"

/*
 * Function:  OpenCats
 * ----------------------
 *  Open the system catalogs and place their entries into the catalog caches. Initialize the buffer
 *  pool control fields.
 *  
 *  returns: OK upon successful execution
 *           NOTOK otherwise
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_CatCache entries of 0 and 1 (RELCAT & ATTRCAT)
 *      
 * ERRORS REPORTED:
 *      NO_CATALOG_FOUND
 *
 * ALGORITHM:
 *    1. Checks for Errors.
 *    2. If catalog files are present, Opens with default values.
 *    3. Reads & updates numRecs and numPgs from relcat.
 *
 * IMPLEMENTATION NOTES:
 *      Uses FindRec from physical layer.
 */

int OpenCats() {
    char *recPtr;
    int i, j, returnValue;
    int relCatNumRecs;
    int relCatNumPgs;
    int attrCatNumRecs;
    int attrCatNumPgs;

    Rid startRid = { 1, 0 }, *foundRid;

    /* Initializing Buffer pool control fields.*/
    g_CacheInUse[0] = g_CacheInUse[1] = TRUE;
    for (i = 2; i < MAXOPEN; i++)
        g_CacheInUse[i] = FALSE;

    for (i = 0; i < MAXOPEN; i++) {
        g_CacheTimestamp[i] = 0;
    }
    /* Creating cache[0] entry for relcat */

    strcpy(g_CatCache[0].relName, RELCAT);
    g_CatCache[0].recLength = 40;
    g_CatCache[0].recsPerPg = 12;
    g_CatCache[0].numAttrs = 6;

    g_CatCache[0].numRecs = 2;
    g_CatCache[0].numPgs = 1;

    g_CatCache[0].relcatRid.pid = 1;
    g_CatCache[0].relcatRid.slotnum = 1;
    g_CatCache[0].relFile = open(RELCAT, O_RDWR);
    g_CatCache[0].dirty = FALSE;
    g_CatCache[0].attrList = createAttributeCatalogRelCat();

    returnValue = FindRec(0, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0, RELCAT, EQ);
    if (returnValue == NOTOK) {
        return ErrorMsgs(NO_CATALOG_FOUND, g_PrintFlag);
    }

    relCatNumRecs = readIntFromByteArray(recPtr, 32);
    relCatNumPgs = readIntFromByteArray(recPtr, 36);

    g_CatCache[0].numRecs = relCatNumRecs;
    g_CatCache[0].numPgs = relCatNumPgs;

    /* Creating cache[1] entry for attrcat */

    strcpy(g_CatCache[1].relName, ATTRCAT);
    g_CatCache[1].recLength = 52;
    g_CatCache[1].recsPerPg = 9;
    g_CatCache[1].numAttrs = 5;

    g_CatCache[1].numRecs = 11;
    g_CatCache[1].numPgs = 2;

    g_CatCache[1].relcatRid.pid = 1;
    g_CatCache[1].relcatRid.slotnum = 2;
    g_CatCache[1].relFile = open(ATTRCAT, O_RDWR);
    g_CatCache[1].dirty = FALSE;
    g_CatCache[1].attrList = createAttributeCatalogAttrCat();

    returnValue = FindRec(0, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0, ATTRCAT, EQ);
    if (returnValue == NOTOK) {
        return ErrorMsgs(NO_CATALOG_FOUND, g_PrintFlag);
    }

    relCatNumRecs = readIntFromByteArray(recPtr, 32);
    relCatNumPgs = readIntFromByteArray(recPtr, 36);

    g_CatCache[1].numRecs = relCatNumRecs;
    g_CatCache[1].numPgs = relCatNumPgs;

    return OK;
}

/*
 * Function:  create_attr_cat_attrcat()
 * ------------------------------------
 *  create linkedlist form of attr_cat of attrcat relation
 *  
 *  returns: pointer to the head of linkedlist
 */

struct attrCatalog* createAttributeCatalogAttrCat() {
    struct attrCatalog *temp, *newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 32;
    (*newNode).length = 20;
    (*newNode).type = STRING;
    strcpy((*newNode).attrName, "relName");
    strcpy((*newNode).relName, ATTRCAT);
    (*newNode).next = NULL;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 12;
    (*newNode).length = 20;
    (*newNode).type = STRING;
    strcpy((*newNode).attrName, "attrName");
    strcpy((*newNode).relName, ATTRCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 8;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "type");
    strcpy((*newNode).relName, ATTRCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 4;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "length");
    strcpy((*newNode).relName, ATTRCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 0;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "offset");
    strcpy((*newNode).relName, ATTRCAT);
    (*newNode).next = temp;
    temp = newNode;

    return temp;
}

/*
 * Function:  create_attr_cat_relcat
 * ----------------------------------
 *  create linkedlist form of attr_cat of relcat relation
 *  
 *  returns: pointer to the head of linkedlist
 */

struct attrCatalog* createAttributeCatalogRelCat() {
    struct attrCatalog *temp, *newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 36;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "numPgs");
    strcpy((*newNode).relName, RELCAT);
    (*newNode).next = NULL;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 32;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "numRecs");
    strcpy((*newNode).relName, RELCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 28;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "numAttrs");
    strcpy((*newNode).relName, RELCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 24;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "recsPerPg");
    strcpy((*newNode).relName, RELCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 20;
    (*newNode).length = 4;
    (*newNode).type = INTEGER;
    strcpy((*newNode).attrName, "recLength");
    strcpy((*newNode).relName, RELCAT);
    (*newNode).next = temp;
    temp = newNode;

    newNode = malloc(sizeof(struct attrCatalog));
    (*newNode).offset = 0;
    (*newNode).length = 20;
    (*newNode).type = STRING;
    strcpy((*newNode).attrName, "relName");
    strcpy((*newNode).relName, RELCAT);
    (*newNode).next = temp;
    temp = newNode;

    return temp;
}
