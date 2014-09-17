
    /* 
	This is a complete file for the front-end.

    */
/*************************************************************
		CONSTANT AND TYPE DEFINITIONS 
*************************************************************/
#define TRUE		1	/* boolean */
#define FALSE		0

#define	OK		0	/* return codes */
#define NOTOK		-1


			/* 
			   parser constants
			   ================ 
					    */

#define	LOWER   500
#define	EQOP	501		/* equality operators code */
#define	GEOP	502
#define	GTOP	503
#define	LEOP	504
#define	NOTEQOP	505
#define LTOP	506
#define	HIGH	507

#define CONTINUE	1	/* indicators */
#define EQUAL		0

#define INPUTLEN	200	/* parser data structure sizes */
#define ROW		40
#define	COLUMN		80
#define MAXLEN		100

#define	PROMPT		"query > "	/* prompt */

/*****************************************************************/

#define MAXPARAS  50
#define PARALEN 	1024


#define	TMP_NAME	"tmp_file"	/* reserved names		      */
#define	PRINT_NAME	"print"
#define	DESTROY_NAME	"destroy"

#define COMMA		100		/* token codes			      */
#define	NUMBER		101
#define	COLON		108
#define LPARAN		109
#define	RPARAN		110
#define ARROW		111
#define LSQR		112
#define RSQR		113
#define	QUOTEDSTR	114
#define	DOT		115
#define SEMI		116
#define	STR		117

					/* Note: Commands codes must be
						 contiguous		      */

#define	CREATEDB	201		/* commands codes - reserved words    */
#define DESTROYDB	202
#define OPENDB		203
#define	CLOSEDB		204
#define	CREATE		205
#define DESTROY		206
#define	LOAD		207
#define PRINT		208
#define SORT		209
#define QUIT		210
#define SELECT		211
#define PROJECT		212
#define JOIN		213
#define INSERT		214
#define DELETE		215
#define INTERSECT	216
#define UNIONOP		217
#define HELP		218
#define BUILDINDEX	219
#define DROPINDEX	220

#define ON		301		/* other reserved words */
#define	KEY		302
#define	SIZE		303
#define IS		304
#define FROM		305
#define INTO		306
#define TO		307
#define WHERE		308
#define AND		309
#define FOR		310

#define	ONE		1		/* action codes */
#define	DONE		0
#define	EAT1		-1
#define EAT3		-3
#define	THROW		-4
#define INC		-5
#define INC2		-6

#define RESULTARG	1		/* arguments position		      */
#define	STDARG		2

#define	LONGSTR		-501		/* error codes			      */
#define UNMATCHQUOTE	-502
#define NOCOMMAND	-503
#define ILLEGAL		-504

/*****************************************************************/

