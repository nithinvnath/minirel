#include <stdio.h>
#include "../include/error.h"
#include "../include/defs.h"

/**
 * Prints out the relevant error messages
 *
 * @param errorId
 */
int ErrorMsgs(int errorId, int printFlag) {
    if (printFlag == OK) {
        printf("<ERROR %d>: ", errorId);
        switch (errorId) {
            case RELNOEXIST:
                printf("Relation does not exist! Please check the name and try again.\n");
                break;
            case ATTRNOEXIST:
                printf("The attribute with given name is not present in the relation.\n");
                break;
            case RELNUM_OUT_OF_BOUND:
                printf("Out of bound relation number encountered\n");
                break;
            case NULL_POINTER_EXCEPTION:
                printf("Null pointer exception!\n");
                break;
            case INVALID_ATTR_TYPE:
                printf("Invalid attribute type! Attribute type should be i, f or s.\n");
                break;
            case INVALID_COMP_OP:
                printf("Invalid comparison operator!\n");
                break;
            case FILE_SEEK_ERROR:
                printf("Error while seeking in file!\n");
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
            case DB_ALREADY_EXISTS:
                printf("A DB with the given name already exists! \
Please provide a different name and try again\n");
                break;
            case ARGC_INSUFFICIENT:
                printf("Argument(s) missing! The number of arguments received is \
less than required number of arguments!\n");
                break;
            case FILE_SYSTEM_ERROR:
                printf("Error occurred while trying to create file/directory. \
Please check file system permissions and try again.\n");
                break;
            case DBNAME_INVALID:
                printf("Database not found with given name! Please check the database name.\n");
                break;
            case REL_ALREADY_EXISTS:
                printf("A relation with given name already exists! Please try again with a \
different name.\n");
                break;
            case INVALID_ATTR_NAME:
                printf("An attribute or relation name is invalid! Names should start with alphabet \
and can be at most 20 characters long.\n");
                break;
            case DB_NOT_OPEN:
                printf("Please call opendb <DBNAME> to open a database first.\n");
                break;
            case DB_NOT_CLOSED:
                printf("Database not closed! Please call CloseDB() before open/create a db \n");
                break;
            case NO_ATTRIBUTES_TO_INSERT:
                printf("Insert has no attribute-value pairs to be inserted into the relation!\n");
                break;
            case ATTR_NOT_IN_REL:
                printf("Attribute with the given name is not found in relation! Please check\
if all attributes are named correctly.\n");
                break;
            case DUPLICATE_TUPLE:
                printf("Tuple already exists in this relation! All tuples must be unique.\n");
                break;
            case METADATA_SECURITY:
                printf("Permission denied! Meta data tables cannot be modified directly.\n");
                break;
            case INTEGER_EXPECTED:
                printf("Integer value was expected but got string instead.\n");
                break;
            case FLOAT_EXPECTED:
                printf("Float value was expected but got string instead.\n");
                break;
            case MAX_STRING_EXCEEDED:
                printf("Exceeded the maximum allowed string size of %d\n",MAX_STRING_SIZE);
                break;
            case PID_OUT_OF_BOUND:
                printf("Trying to read a page which is greater than the number of \
pages in the relation.\n");
                break;
            case DBNAME_EXCEED_LIMIT:
                printf("Database Name exceeded the limit! Enter name within 20 characters.\n");
                break;
            case TYPE_MISMATCH:
                printf("Type Mismatch while performing Join! Please try similar attributes.\n");
                break;
            case REL_NOT_EMPTY:
                printf("Relation is not empty! One can load only on to empty relations.\n");
                break;
            case INVALID_FILE:
                printf("Cannot open file! Please check the path given and try again.\n");
                break;
            case PAGE_OVERFLOW:
                printf("MINIREL cannot handle a record of size > %d. Please try again with \
lesser number of attributes or arguments with smaller size.\n", MAXRECORD);
                break;
            case INSUFFICIENT_ATTRS:
                printf("Number of attributes mismatch! Please pass all the attributes present and \
its values to insert a new record. Use \n\t select into <some_name> from attrcat where (relName = \"<RELNAME>\"\
);\n to find the attributes for a relation\n");
                break;
            default:
                printf("Unexpected error! Please don't reduce marks for this :)\n");
                break;
        }
    }
    return NOTOK;
}
