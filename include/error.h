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
void ErrorMsgs(int errorId);

#endif
