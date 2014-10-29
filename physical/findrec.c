#include "../include/globals.h"
#include "../include/error.h"
#include "helpers.c"
#include <stdlib.h>

/**
 * Starting at record startRid in relation relNum, find the RID of the next
 * record that meets the specification.
 *
 * @param relNum
 * @param startRid   - The search will begin with the first record after startRid.
 * @param foundRid   - The record identifier of the first record after that specified by startRid
 *                     NULL if not found
 * @param recPtr     - A pointer to a record-sized byte array into which the contents of the
 *                     matching record (if any) will be put.
 * @param attrType   - The data type (i, f or s) of the search attribute.
 * @param attrSize   - Length of search attribute in bytes
 * @param attrOffset - The offset into the record at which the search attribute is located.
 * @param valuePtr   - A pointer to a byte array which contains the search value
 * @param compOp     - Comparison operator
 */
void FindRec(int relNum, const Rid *startRid, Rid *foundRid, char *recPtr, const char attrType,
        const int attrSize, const int attrOffset, const char *valuePtr, const int compOp) {

    unsigned short pid = startRid->pid;
    ReadPage(relNum, pid);
    int intAttr;
    float floatAttr;
    char* stringAttr;

    switch (attrType) {
        case 'i':
            intAttr = readIntFromByteArray(recPtr,attrOffset);
            break;
        case 'f':
            floatAttr = readFloatFromByteArray(recPtr, attrOffset);
            break;
        case 's':
            stringAttr = (char *) malloc(sizeof(char)*attrSize);
            readStringFromByteArray(stringAttr,recPtr, attrOffset, attrSize);
            break;
        default:
            ErrorMsgs(INVALID_ATTR_TYPE);
            return;
            break;
    }

    while(GetNextRec(relNum,startRid,foundRid,recPtr)){

    }

}
