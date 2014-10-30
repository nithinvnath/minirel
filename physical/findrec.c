#include <stdlib.h>

#include "../include/globals.h"
#include "../include/error.h"
#include "../include/getnextrec.h"
#include "../include/findrec.h"
#include "../include/helpers.h"

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
int FindRec(int relNum, const Rid *startRid, Rid *foundRid, char *recPtr, const char attrType,
        const int attrSize, const int attrOffset, const char *valuePtr, const int compOp) {

    unsigned short pid = startRid->pid;
    ReadPage(relNum, pid);
    int intAttr, intAttr2;
    float floatAttr, floatAttr2;
    char *stringAttr, *stringAttr2;
    stringAttr = (char *) malloc(sizeof(char) * attrSize);
    stringAttr2 = (char *) malloc(sizeof(char) * attrSize);

    while (GetNextRec(relNum, startRid, foundRid, recPtr)) {
        switch (attrType) {
            case 'i':
                intAttr = readIntFromByteArray(valuePtr, 0);
                intAttr2 = readIntFromByteArray(recPtr, attrOffset);
                if (compareNum((float) intAttr, (float) intAttr2, compOp)) {
                    return OK;
                }
                break;
            case 'f':
                floatAttr = readFloatFromByteArray(valuePtr, 0);
                floatAttr2 = readFloatFromByteArray(recPtr, attrOffset);
                if (compareNum(floatAttr, floatAttr2, compOp)) {
                    return OK;
                }
                break;
            case 's':
                readStringFromByteArray(stringAttr, valuePtr, 0, attrSize);
                readStringFromByteArray(stringAttr2, recPtr, attrOffset, attrSize);
                if (compareStrings(stringAttr, stringAttr2, compOp)) {
                    return OK;
                }
                break;
            default:
                ErrorMsgs(INVALID_ATTR_TYPE);
                return NOTOK;
                break;
        }
    }
    return NOTOK;
}
