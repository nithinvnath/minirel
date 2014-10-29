#include "../include/error.h"

/**
 * Prints out the relevant error messages
 *
 * @param errorId
 */
ErrorMsgs(int errorId) {
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
        default:
            printf("Unexpected error!\n");
            break;
    }
}
