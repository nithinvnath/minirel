#include "../include/helpers.h"

/*
 * Contains helper functions used throughout the project
 *
 *  Created on: 29-Oct-2014
 *      Author: nithin, dheeraj
 */
int readStringFromByteArray(char * string, const char *byteArray, const int offset, const int size) {
    if (byteArray == NULL || string == NULL) {
        return ErrorMsgs(NULL_POINTER_EXCEPTION, g_PrintFlag);
    }
    strncpy(string, (byteArray + offset), size);
    return OK;
}

int readIntFromByteArray(const char *byteArray, const int offset) {
    int val;
    memcpy(&val, byteArray + offset, sizeof(int));
    return val;
}

float readFloatFromByteArray(const char* byteArray, const int offset) {
    float val;
    memcpy(&val, byteArray + offset, sizeof(float));
    return val;
}

void convertIntToByteArray(int value, char *byteArray) {
    memcpy(byteArray, (void *) &value, sizeof(int));
}

void convertFloatToByteArray(float value, char *byteArray) {
    memcpy(byteArray, (void *) &value, sizeof(int));
}

/*************************************************************
 COMPARISONS
 *************************************************************/

bool compareNum(float val1, float val2, int compOp) {
    switch (compOp) {
        case EQ:
            return val1 == val2 ? TRUE : FALSE;
        case NEQ:
            return val1 != val2 ? TRUE : FALSE;
        case GEQ:
            return val1 >= val2 ? TRUE : FALSE;
        case LEQ:
            return val1 <= val2 ? TRUE : FALSE;
        case GT:
            return val1 > val2 ? TRUE : FALSE;
        case LT:
            return val1 < val2 ? TRUE : FALSE;
        default:
            ErrorMsgs(INVALID_COMP_OP, g_PrintFlag);
            break;
    }
    return FALSE;
}

bool compareStrings(char *s1, char *s2, int compOp) {
    switch (compOp) {
        case EQ:
            return strcmp(s1, s2) == 0 ? TRUE : FALSE;
        case NEQ:
            return strcmp(s1, s2) ? TRUE : FALSE;
        case GEQ:
            return (strcmp(s1, s2) >= 0) ? TRUE : FALSE;
        case LEQ:
            return (strcmp(s1, s2) <= 0) ? TRUE : FALSE;
        case GT:
            return (strcmp(s1, s2) > 0) ? TRUE : FALSE;
        case LT:
            return (strcmp(s1, s2) < 0) ? TRUE : FALSE;
        default:
            ErrorMsgs(INVALID_COMP_OP, g_PrintFlag);
            break;
    }
    return FALSE;
}
/**
 * Gets the last valid Rid in a relation
 *
 * @param   relNum
 * @return  last valid Rid
 */
Rid getLastRid(int relNum) {
    int numRecs = g_CatCache[relNum].numRecs;
    int recsPerPg = g_CatCache[relNum].recsPerPg;
    Rid last;
    last.pid = numRecs / recsPerPg + 1;
    last.slotnum = numRecs % recsPerPg + 1;
    return last;
}

/*
 * Function: separate_db_path() 
 * ----------------------------
 * Separates dbname and path from the the string, dbname with path
 *
 *  db_with_path : full path of database
 *  path         : path of database without dbname
 *  dbname       : database name
 *
 *  returns: OK on success
 *           NOTOK on failure
 */

int separateDBPath(char* fullDBPath, char* path, char* dbName) {

    char fullDBPathCopy[MAXPATH];
    strcpy(fullDBPathCopy, fullDBPath);

    char *temp = strtok(fullDBPathCopy, "/");
    strcpy(dbName, temp);
    if (fullDBPath[0] == '/') {
        strcpy(path, "/");
    } else {
        strcpy(path, "");
    }

    if (fullDBPath == NULL)
        return NOTOK;

    if (strlen(temp) != strlen(fullDBPath)) {
        while ((temp = strtok(NULL, "/")) != NULL) {
            strcat(path, dbName);
            strcat(path, "/");

            strcpy(dbName, temp);
        }
    }

    if (strlen(dbName) > RELNAME)
        return ErrorMsgs(DBNAME_EXCEED_LIMIT, g_PrintFlag);
    path[strlen(path) - 1] = '\0';
    return OK;
}

/*************************************************************
 HELPERS FOR SCHEMA LAYER
 *************************************************************/

/**
 * Compares two records byte by byte
 * 
 * @param record1
 * @param record2
 * @param sizeOfRecord
 * @return
 */
int compareRecords(char *record1, char *record2, int sizeOfRecord) {
    int i;
    for (i = 0; i < sizeOfRecord; ++i) {
        if (record1[i] != record2[i]) {
            break;
        }
    }
    return (i != sizeOfRecord) ? NOTOK : OK;
}

/**
 *  Gets the N from sN
 * @param sN
 * @return
 */
int getN(char *sN) {
    int i, N;
    N = atoi(sN + 1);
    return N;
}

/**
 * Checks if the string is valid
 * STRING: A character set that starts with an alphabet
 * and is followed by an arbitrary number of alphabets and digits
 *
 * @param string
 * @return OK if valid
 */
int isValidString(char *string) {
    if (!isalpha(string[0])) {
        return NOTOK;
    } else if (strlen(string) >= RELNAME) {
        return NOTOK;
    } else {
        return OK;
    }
}

/**
 * Get size of attribute from attributeFormat
 *
 * @param attrFormat
 * @return size of the attribute
 */
int getSizeOfAttr(char *attrFormat) {
    int size = 0;
    switch (attrFormat[0]) {
        case INTEGER:
            size = sizeof(int);
            break;
        case STRING:
            size = getN(attrFormat);
            break;
        case FLOAT:
            size = sizeof(float);
            break;
        default:
            break;
    }
    return size;
}

/**
 * Gets the attribute catalog using the attribute name
 *
 * @param attrList
 * @param attrName
 * @return the attrCatalog struct
 */
struct attrCatalog* getAttrCatalog(struct attrCatalog* attrList, char *attrName) {
    while (attrList != NULL) {
        if (strcmp(attrName, attrList->attrName) == 0) {
            break;
        }
        attrList = attrList->next;
    }
    return attrList;
}

