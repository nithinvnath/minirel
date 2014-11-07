#ifndef ERROR_H_
#define ERROR_H_

/************************************************************
   This file contains the error constants that are
   used by the routine that reports error messages.
   As you find error conditions to report, 
   make additions to this file. 
************************************************************/

#define RELNOEXIST                  101     /* Relation does not exist */
#define ATTRNOEXIST                 102     /* Attribute does not exist */
#define RELNUM_OUT_OF_BOUND         103     /* Relation number is out of bound */
#define NO_ATTRS_FOUND              104     /* No attributes found in relation */
#define NULL_POINTER_EXCEPTION      105     /* Null pointer exception */
#define INVALID_ATTR_TYPE           106     /* Invalid attribute type   */
#define INVALID_COMP_OP             107     /* Invalid comparison operator */
#define FILE_SEEK_ERROR             108     /* Error while seeking file */
#define NO_CATALOG_FOUND            109     /* No catalog found */
#define NULL_ARGUMENT_RECEIVED      110     /* Null argument received where non null was expected */
#define CAT_FILE_ALREADY_EXIST      111     /* Can't create cat files as they exists */
#define WRITE_DISK_ERROR            112     /* Error occurred while making write system call */
#define READ_DISK_ERROR             113     /* Error occurred while making read system call */
#define FILE_SYSTEM_ERROR           114     /* Error while creating directory/file */
#define DB_ALREADY_EXISTS           115     /* DB with same name already exists */
#define ARGC_INSUFFICIENT           116     /* Number of arguments received is less than expected*/
#define DBNAME_INVALID              117     /* Database with given name doesn't exist */
#define REL_ALREADY_EXISTS          118     /* Relation name already exists */
#define INVALID_ATTR_NAME           119     /* string starts with num/length>20 */
#define DB_NOT_CLOSED               120     /* tried to create/open db without closing current db */
#define DB_NOT_OPEN                 121     /* Open the db first */
#define NO_ATTRIBUTES_TO_INSERT     122     /* Insufficient number of arguments received */
#define ATTR_NOT_IN_REL             123     /* The attribute name in insert is not part of relation */
#define DUPLICATE_TUPLE             124     /* The tuple trying to be inserted already exists */
#define METADATA_SECURITY           125     /* User trying to modify relcat or attrcat tables*/
#define DBNAME_EXCEED_LIMIT         126     /* Database Name Exceeded */
#define INTEGER_EXPECTED            127     /* Integer value was expected but got string */
#define FLOAT_EXPECTED              128     /* Float value was expected but got string */
#define MAX_STRING_EXCEEDED         129     /* String size given exceeded the defined one */
#define PID_OUT_OF_BOUND            130     /* Trying to read a page out of bound */
#define TYPE_MISMATCH               131     /* Type Mismatch while performing join */ 

int ErrorMsgs(int errorId, int printFlag);

#endif
