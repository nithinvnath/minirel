    /* 
    This is the basic definition file.
    */
#ifndef DEFS_H_
#define DEFS_H_
//FIXME move PATH to better location?
/*************************************************************
        CONSTANTS
*************************************************************/
#define PAGESIZE    512    /* number of bytes in a page */
#define    MAXRECORD    508    /* PAGESIZE minus number of bytes taken up
                                   for slot map */
#define MAXPATH        100  /* maximum path length that can be given */
#define RELNAME        20    /* max length of a relation name */
#define MAXOPEN        20      /* max number of files that can be open
                                   at the same time */

#define    OK        0    /* return codes */
#define NOTOK        -1

#define RELCAT        "relcat"   /* name of the relation catalog file */
#define ATTRCAT        "attrcat"  /* name of the attribute catalog file */

#define RELCAT_CACHE    0
#define ATTRCAT_CACHE   1

#define PATH ".minirel_data"

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

typedef union Flip{
    float float_val;
    int int_val;
}Flip;

/*****************************************************************/

#endif /* DEFS_H_ */
