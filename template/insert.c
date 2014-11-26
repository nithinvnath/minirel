/************************INCLUDES*******************************/
#include "../include/defs.h"
#include "../include/error.h"
#include "../include/globals.h"
#include <string.h>
#include <stdio.h>

/************************EXTERNS********************************/

extern OpenRel();
extern CloseRel();
extern GetNextRec();
extern InsertRec();
extern FindRelNum();
extern Errormsgs();

/************************LOCAL DEFINES**************************/


/*------------------------------------------------------------

FUNCTION Insert (argc, argv)

PARAMETER DESCRIPTION: 
       argc is the count of the arguments in the command line.
       argv is the pointer to the array of pointers pointing to
       the argument strings.

SPECIFICATIONS:
       argv[0] = "insert"
       argv[1] = relation name
       argv[2] = attribute name 1
       argv[3] = attribute value 1
       ...
       argv[argc-2] = attribute name N
       argv[argc-1] = attribute value N
       argv[argc] = NIL

       The routine is to implement the relational update operator "insert".
       The tuple given in argv is to be inserted into the named relation.
       Input values, which will be in ASCII form, are to be converted
       appropriately, according to their specified format. Attributes
       are to be matched up by name. Length of incoming string-type
       data should be regulated. If it is too long, truncate it. If
       it is too short, pad with NULLs. Inserting the tuple should not
       introduce a duplicate. Any errors in the command are to be reported.

ALGORITHM:
       1) Check for valid command.
       2) Check that the append relation is neither the relation catalog
	  nor the attribute catalog.
       3) Check that the relation exists, and if it does, open it.
       4) Check that the number of attribute arguments corresponds to that
	  of the relation.
       5) Check that the attribute arguments are unique, and that they match
	  up with the relation's attributes.
       6) Create the tuple to be appended using the information in the 
	  relation's attribute catalog and the values given in argv.
       7) Compare the created tuple with every tuple in the relation, to
	  check whether the created tuple already exists in the relation.
       8) If it exists, generate an error message. Otherwise, insert the
	  created tuple into the relation.
       9) Close the relation.

WRITTEN ON:
       1/8/94

AUTHOR:
       P.V. Narasimha Rao 

BUGS:
       None found as of date.

ERRORS REPORTED:
       1) BADCOMMAND        - Invalid relational operator
       2) RELNOEXIST        - Append relation does not exist
       3) WRONGNUMARGS      - Wrong number of arguments for routine
       4) DUPLICATEATTR     - Attribute specified more than once
       5) ATTRNOEXIST       - Invalid relation attribute
       6) RECORDEXIST       - Record already exists
       7) BADATTRTYPE       - Invalid attribute type
       8) CATACCESS         - Tried to append to catalogs
       9) CALLOCERROR       - Error in call to calloc()

GLOBAL VARIABLES MODIFIED:
       None.
         
IMPLEMENTATION NOTES (IF ANY):
       Where the new record is inserted in the relation depends on the
       implementation of InsertRec().

------------------------------------------------------------*/
Insert (argc, argv)
int	argc;
char	**argv;

{
/*
	    .
	    .

	< Your C statements > 

	    .
	    .
	    .*/


     return (OK);  /* all's fine */
}  /* insert */


