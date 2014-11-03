#include <stdio.h>
#include "../include/error.h"
#include "../include/defs.h"

/**
 * Prints out the relevant error messages
 *
 * @param errorId
 */
int ErrorMsgs(int errorId, int printFlag) {
    if (printFlag) {
        printf("<ERROR %d>: ", errorId);
        switch (errorId) {
            case RELNOEXIST:
                printf("Relation does not exist!\n");
                break;
            case ATTRNOEXIST:
                printf("Attribute does not exist!\n");
                break;
            case RELNUM_OUT_OF_BOUND:
                printf("Out of bound relation number encountered\n");
                break;
            case NULL_POINTER_EXCEPTION:
                printf("Null pointer exception!\n");
                break;
            case INVALID_ATTR_TYPE:
                printf("Invalid attribute type!\n");
                break;
            case INVALID_COMP_OP:
                printf("Invalid comparison operator!\n");
                break;
            case FILE_SEEK_ERROR:
                printf("Error while seeking!\n");
                break;
            case NULL_ARGUMENT_RECEIVED:
                printf("A NULL argument was received where non-NULL was required!\n");
                break;
            case WRITE_DISK_ERROR:
                printf("Error occurred while writing data to disk!\n");
                break;
            case READ_DISK_ERROR:
                printf("Error occurred while reading data from disk!\n");
                break;
            case NO_ATTRS_FOUND:
                printf("No attributes found for the relation!\n");
                break;
            case NO_CATALOG_FOUND:
                printf("No catalog found in the database!\n");
                break;
            case CAT_FILE_ALREADY_EXIST:
                printf("catalog file(s) already exist in the database!\n");
                break;
            default:
                printf("Unexpected error!\n");
                break;
        }
    }
    return NOTOK;
}
