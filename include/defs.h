    /* 
    This is the basic definition file.
    */
#ifndef DEFS_H_
#define DEFS_H_

/*************************************************************
        CONSTANTS
*************************************************************/
#define PAGESIZE    512    /* number of bytes in a page */
#define    MAXRECORD    508    /* PAGESIZE minus number of bytes taken up
                                   for slot map */

#define RELNAME        20    /* max length of a relation name */
#define MAXOPEN        20      /* max number of files that can be open
                                   at the same time */

#define    OK        0    /* return codes */
#define NOTOK        -1

#define RELCAT        "relcat"   /* name of the relation catalog file */
#define ATTRCAT        "attrcat"  /* name of the attribute catalog file */

/*************************************************************
        COMPARISON OPERATORS
*************************************************************/
#define EQ  501     //=
#define GEQ 502     //>=
#define GT  503     //>
#define LEQ 504     //<=
#define NEQ 505     //<>
#define LT  506     //<

/*************************************************************
        TYPE DEFINITIONS
*************************************************************/

/* Rid structure */
typedef struct recid {
    short    pid;
    short    slotnum;
} Rid;


/* Page Structure */
typedef struct ps {
    unsigned slotmap;
    char contents [MAXRECORD];
} Page;

/* Boolean*/
typedef enum bool{
    FALSE,
    TRUE
}bool;

/* Data types */
typedef enum type{
    INTEGER='i',
    FLOAT='f',
    STRING='s'
}datatype;

/*****************************************************************/

#endif /* DEFS_H_ */
