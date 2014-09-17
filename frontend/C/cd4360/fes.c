#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "fes.h"


typedef struct {			/* parser table entry		      */
	short	find,
		tcode,
		action,
		next;
} PARSER_TABLE;


PARSER_TABLE table [21] [20] = {
{   	{   	0, 	CREATEDB, 	EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	SEMI, 		DONE, 		0	}	},
{   	{   	0, 	DESTROYDB, 	EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	SEMI, 		DONE, 		0	}	},
{   	{   	0, 	OPENDB, 	EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	SEMI, 		DONE, 		0	}	},
{   	{   	0, 	CLOSEDB, 	EAT1, 		0	},
    	{	1, 	SEMI, 		DONE, 		0	}	},
{   	{   	0, 	CREATE,		EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	LPARAN, 	THROW, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	EQOP, 		THROW, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	COMMA, 		THROW, 		3	},
	{	0,	RPARAN,		THROW,		0	},
    	{	1, 	SEMI, 		DONE, 		0	}	},
{   	{   	0, 	DESTROY, 	EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{	1, 	SEMI, 		DONE, 		0	}	},
{   	{  	0, 	LOAD, 		EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
    	{  	1, 	FROM, 		THROW, 		0	},
    	{	1, 	STR,		EAT1, 		0	},
    	{   	1, 	SEMI, 		DONE, 		0	}	},
{   	{   	0, 	PRINT, 		EAT1, 		0	},
    	{	1, 	STR, 		EAT1, 		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	SORT,		EAT1,		0	},
	{	1,	INTO,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	FROM,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	ON,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	QUIT,		EAT1,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	SELECT,		EAT1,		0	},
	{	1,	INTO,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	FROM,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	WHERE,		THROW,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	EQOP,		EAT3,		14	},
	{	0,	GEOP,		EAT3,		14	},
	{	0,	GTOP,		EAT3,		14	},
	{	0,	LEOP,		EAT3,		14	},
	{	0,	NOTEQOP,	EAT3,		14	},
	{	0,	LTOP,		EAT3,		0	},
	{	1,	NUMBER,		EAT1,		16	},
	{	0,	QUOTEDSTR,	EAT1,		0	},
	{	1, 	AND,		THROW,		8	},
	{	0,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	PROJECT,	EAT1,		0	},
	{	1,	INTO,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	FROM,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1, 	COMMA,		THROW,		6	},
	{	0,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	JOIN,		EAT1,		0	},
	{	1,	INTO,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	DOT,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	COMMA,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	DOT,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	INSERT,		EAT1,		0	},
	{	1,	INTO,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	EQOP,		THROW,		0	},
	{	1,	NUMBER,		EAT1,		8	},
	{	0,	QUOTEDSTR,	EAT1,		0	},
	{	1,	COMMA,		THROW,		4	},
	{	0,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	DELETE,		EAT1,		0,	},
	{	1,	FROM,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	WHERE,		THROW,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	EQOP,		EAT3,		12	},
	{	0,	GEOP,		EAT3,		12	},
	{	0,	GTOP,		EAT3,		12	},
	{	0,	LEOP,		EAT3,		12	},
	{	0,	NOTEQOP,	EAT3,		12	},
	{	0,	LTOP,		EAT3,		0	},
	{	1,	NUMBER,		EAT1,		14	},
	{	0,	QUOTEDSTR,	EAT1,		0	},
	{	1, 	AND,		THROW,		5	},
	{	0,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	INTERSECT,	EAT1,		0	},
	{	1,	INTO,		THROW,		3	},
	{	0,	FROM,		INC,		5	},
	{	1,	STR,		EAT1,		0	},
	{	1,	FROM,		THROW,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	UNIONOP,	EAT1,		0	},
	{	1,	INTO,		THROW,		3	},
	{	0,	FROM,		INC,		5	},
	{	1,	STR,		EAT1,		0	},
	{	1,	FROM,		THROW,		0	},
	{	1,	LPARAN,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	RPARAN,		THROW,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	HELP,		EAT1,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	BUILDINDEX,	EAT1,		0	},
	{	1,	FOR,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	ON,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	SEMI,		DONE,		0	}	},
{	{	0,	DROPINDEX,	EAT1,		0	},
	{	1,	FOR,		THROW,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	ON,		THROW,		5	},
	{	0,	SEMI,		DONE,		0	},
	{	1,	STR,		EAT1,		0	},
	{	1,	SEMI,		DONE,		0	}	},
};


parser ()
{
char	buff[ BUFSIZ + 2 ],
	params [ MAXPARAS  ] [ PARALEN ],
	*ptr [ MAXPARAS ];
short	loop,
	rcode;

	do {					/* loop until 'getquery'      */
	   for (loop = 0 ; loop < (MAXPARAS ) ; loop++)
	       ptr [loop] = params [loop];

	    getinput (buff);			/* returns a DONE code        */
	    rcode = processquery (buff, ptr);
	} while (rcode == CONTINUE);

} /* parser */


/*	getinput

	This routine places a input query into the 'buff' passed in.
	Characters after a semi-colon are discarded.
	If the query is longer than the length of 'buff', extra characters will
	be discarded.
	Tabs and linefeeds inside a query are converted to spaces.

	*** You must end each query with a semicolon and a linefeed. ***
	*** Semicolon is used for ending a query. You cannot use it  ***
	*** even within double quotes.				     ***
*/

getinput (buff)
char	buff[];
{
int	i;

    while (TRUE) {	/* loop forever       */
	printf (PROMPT);
	i = 0;
	while ((buff[i] = getchar ()) == ' ' ||	/* get rid of space   */
		buff[i] == '\t');			/* get rid of tab     */
	if (buff[i] != '\n') {			/* not a linefeed     */
	    while (i < BUFSIZ && buff[i] != ';') {
		i++;
		buff[i] = getchar ();
		if (buff[i] == '\t')	       /* change tab to space */
		    buff[i] = ' ';
		if (buff[i] == '\n')	       /* change linefeed to  */
		    buff[i] = ' ';		       /* to space            */
	    }

	    if (buff[i] != ';') {			/* query longer than  */
		while (getchar () != ';');		/* buffer size, get   */
		buff[BUFSIZ] = ';';		/* rid of the rest    */
	    }

	    while (getchar () != '\n');		/* look for a linefeed*/

	    if (i != 0) {				/* if not a single ';'*/
		i++;				
		buff[i] = '\0';			/* pad a null at end  */
		printf ("\n%s\n", buff);	/* echo the query     */
		return (OK);			/* exit the loop      */
	    }
	}
    }
} /* getinput */


processquery (buff, ptr)
char	*buff;
char	**ptr;
{
char	tokenbuff [ PARALEN ],
	*buffstart;
short	loop,
	len, 
	command,
	state,
	scount,
	pcount;
int tcode;

	buffstart = buff;

	for (loop = 0 ; loop < (MAXPARAS ) ; loop++) 
	    ptr [loop] [0] = '\0';

	tcode = findtoken (buff, tokenbuff, &len);
	if ((tcode >= CREATEDB) && (tcode <= DROPINDEX)) {
	    command = tcode - CREATEDB;
	    state = 0;
	    pcount = 0;
	    loop = 1;
	    do {
	        if (table[command][state].find)
		    tcode = findtoken (buff, tokenbuff, &len);
		if (tcode == table[command][state].tcode) {
		    switch (table[command][state].action) {
			case DONE :
			    loop = 0;
			    break;
			case EAT1 :
			    strcpy (ptr[pcount], tokenbuff);
			    pcount += ONE;
			    break;
			case EAT3 :
			    memcpy(ptr[pcount], &tcode, sizeof(int));
			    pcount += ONE;
			    break;
			case INC :
			    pcount += ONE;
			    break;
			case INC2 :
			    pcount += 2;
			    break;
			case THROW :
			    break;
			default :
			    scount = table[command][state].action;
			    if ((tcode >= EQOP) && (tcode <= LTOP))
				memcpy(ptr[scount], &tcode, sizeof(int));
			    else strcpy (ptr[scount], tokenbuff);
		    }
		    buff += len;
		    if (table[command][state].next)
			state = table[command][state].next;
		    else
		        state += 1;
		} else if (table[command][state + 1].find == 0 &&
		           table[command][state + 1].tcode != 0)
		    state += 1;
		else {
		    synerror (buffstart, buff, command, state, tcode);
		    return (CONTINUE);
		}
	    } while (loop);
	} else {
	    synerror (buffstart, buff, 0, 0, NOCOMMAND);
	    return (CONTINUE);
	}

        ptr[pcount] = NULL;

	switch (command + CREATEDB) {
	    case CREATEDB :
		CreateDB (pcount, ptr);
		break;
	    case DESTROYDB :
		DestroyDB (pcount, ptr);
		break;
	    case OPENDB :
		OpenDB (pcount, ptr);
		break;
	    case CLOSEDB :
		CloseDB (pcount, ptr);
		break;
	    case CREATE :
		Create (pcount, ptr);
		break;
	    case DESTROY :
		Destroy (pcount, ptr);
		break;
	    case LOAD :
		Load (pcount, ptr);
		break;
	    case PRINT :
		Print (pcount, ptr);
		break;
	    case BUILDINDEX :
		BuildIndex(pcount, ptr);
		break;
	    case DROPINDEX :
		DropIndex(pcount, ptr);
		break;
	    /*
	    case SORT :
		Sort (pcount, ptr);
		break;
            */
	    case QUIT :
		Quit (pcount, ptr);
		return (DONE);
	    case SELECT :
		Select (pcount, ptr);
		break;
	    case PROJECT :
		Project (pcount, ptr);
		break;
	    case JOIN :
		Join (pcount, ptr);
		break;
	    case INSERT :
		Insert (pcount, ptr);
		break;
	    case DELETE :
		Delete (pcount, ptr);
		break;
            /*
	    case INTERSECT :
		printf ("intersect not yet implemented\n");
		break;
	    case UNIONOP :
		printf ("union not yet implemented\n");
		break;
	    case HELP :
		printf ("help not yet implemented\n");
		break;
             */
	}
	return (CONTINUE);
} /* processquery */


synerror (start, error_at, command, state, tcode)
char	*start,
	*error_at;
short	command,
	state,
	tcode;
{
short	i, len, more;

	len = (int) error_at - (int) start;
	for (i = 0 ; i < len ; i++)
	    printf (" ");
	while (*error_at == ' ') {
	    error_at++;
	    printf (" ");
	}
	printf ("^\nSyntax error: ");

	switch (tcode) {
	    case NOCOMMAND :
	        printf ("command expected\n");
	        return (OK);
	    case LONGSTR :
	        printf ("string too long\n");
	        return (OK);
	    case UNMATCHQUOTE :
	        printf ("unmatched quote\n");
	        return (OK);
	    case ILLEGAL :
		printf ("illegal character\n");
		return (OK);
	    default : ;
	}

	state += 1;
	more = 0;
	do {
	    state -= 1;
	    if (more)
		printf (", ");
	    switch (table[command][state].tcode) {
		case STR :
		    printf ("string");
		    break;
		case QUOTEDSTR :
		    printf ("quoted string");
		    break;
		case NUMBER :
		    printf ("number");
		    break;
		case EQOP :
		    printf ("'='");
		    break;
		case GEOP :
		    printf ("'>='");
		    break;
		case GTOP :
		    printf ("'>'");
		    break;
		case LEOP :
		    printf ("'<='");
		    break;
		case NOTEQOP :
		    printf ("'<>'");
		    break;
		case LTOP :
		    printf ("'<'");
		    break;
		case COMMA :
		    printf ("','");
		    break;
		case COLON :
		    printf ("':'");
		    break;
		case LPARAN :
		    printf ("'('");
		    break;
		case RPARAN :
		    printf ("')'");
		    break;
		case LSQR :
		    printf ("'['");
		    break;
		case RSQR :
		    printf ("']'");
		    break;
		case ARROW :
		    printf ("'^'");
		    break;
		case SEMI :
		    printf ("';'");
		    break;
		case KEY :
		    printf ("key");
		    break;
		case SIZE :
		    printf ("size");
		    break;
		case IS :
		    printf ("is");
		    break;
		case FROM :
		    printf ("from");
		    break;
		case INTO :
		    printf ("into");
		    break;
		case TO :
		    printf ("to");
		    break;
		case AND :
		    printf ("and");
		    break;
		case WHERE :
		    printf ("where");
		    break;
		case FOR :
		    printf ("for");
		    break;
		default :
		    printf ("something else");
	    }
	    more = 1;
	} while (table[command][state].find != 1);

	printf (" expected\n");
	return (OK);

} /* synerror */


/*	findtoken 

	Only the following tokens are stored in the token buffer:
		string	
		quoted string 
		number
	Number will be stored in ascii form. (i.e. no conversion is done)

	Variable 'count' keeps track of the number of characters placed into
	the token buffer. Error code is returned when the token buffer is 
	filled up.
*/

findtoken (p, tokenp, len)
char	*p,				/* pointer to input buffer 	      */
	*tokenp;			/* pointer to token buffer 	      */
short	*len;				/* pointer to token length variable   */
{
	char	*btokenp;		/* pointer to beginning of token buff */
	short   count;			/* length of a string		      */
	int	iv;
	float	fv;


	btokenp = tokenp;		/* remember the beginning position of */
					/* token buffer			      */
	*len = 0;			/* initialize token length to zero    */
	count = 0;			/* initialize string length to zero   */

	while (*p == ' ') {		/* get rid of spaces		      */
	    p++;
	    *len += 1;
	}

	switch (*p) {			/* look at the first character        */

	case '0' :			/* integer and real number     	      */
	case '1' :
	case '2' :
	case '3' :
	case '4' :
	case '5' :
	case '6' :
	case '7' :
	case '8' :
	case '9' :
	    while (isdigit (*p)) {	/* digits before a decimal point      */
		*tokenp = *p;		/* copy one digit to token buffer     */
		tokenp++;		/* increment token buffer pointer     */
		p++;			/* increment input buffer pointer     */
		*len += 1;		/* increment token length	      */
		count++;		/* increment string count	      */
		if (count >= MAXLEN)    /* string too long		      */
		    return (LONGSTR);
	    }
	    if (*p == '.') {		/* decimal point if one exists        */
		do {
		    *tokenp = *p;
		    tokenp++;
		    p++;
		    *len += 1;
		    count++;
		    if (count >= MAXLEN)
			return (LONGSTR);
		} while (isdigit (*p));	/* digits after the decimal point     */
	    }
	    *tokenp = '\0';		/* pad a null byte after the number   */

	    return (NUMBER);

	case '=' :
	    *len += 1;
	    return (EQOP);

	case '>' :
	    p++;
	    if (*p == '=') {
		*len += 2;
		return (GEOP);
	    }
	    *len += 1;
	    return (GTOP);
	case '<' :
	    p++;
	    if (*p == '=') {
		*len += 2;
		return (LEOP);
	    } else if (*p == '>') {
		*len += 2;
		return (NOTEQOP);
	    }
	    *len += 1;
	    return (LTOP);

	case '.':
	    *len += 1;
	    return (DOT);

	case ',':
	    *len += 1;
	    return (COMMA);

	case ':' :
	    *len += 1;
	    return (COLON);

	case '(' :
	    *len += 1;
	    return (LPARAN);

	case ')' :
	    *len += 1;
	    return (RPARAN);

	case '^' :
	    *len += 1;
	    return (ARROW);

	case '[' :
	    *len += 1;
	    return (LSQR);

	case ']' :
	    *len += 1;
	    return (RSQR);

	case '"' :				/* quoted string	      */
	    p++;				/* store characters within    */
	    *len += 1;				/* quotes into token buffer   */
	    while (*p != '"') {
		if (*p == ';')			/* unterminated string	      */
		    return (UNMATCHQUOTE);
		*tokenp = *p;
		tokenp++;
		p++;
		*len += 1;
		count++;
		if (count >= MAXLEN)
		    return (LONGSTR);
	    }
	    *tokenp = '\0';			/* pad a null at the end     */
	    *len += 1;
	    return (QUOTEDSTR);

	case ';' :
	    return (SEMI);

	default :				/* string		      */
            while (isalpha (*p) || isdigit (*p) || *p == '/' || *p == '-') {
		*tokenp = *p;
		tokenp++;
		p++;
		*len += 1;
		count++;
		if (count >= MAXLEN)
		    return (LONGSTR);
	    }
	    *tokenp = '\0';			/* pad a null character       */

	    /* key words		      */

	    if (strcmp (btokenp, "createdb") == EQUAL) return (CREATEDB);
	    if (strcmp (btokenp, "destroydb") == EQUAL) return (DESTROYDB);
	    if (strcmp (btokenp, "opendb") == EQUAL) return (OPENDB);
	    if (strcmp (btokenp, "closedb") == EQUAL) return (CLOSEDB);
	    if (strcmp (btokenp, "create") == EQUAL) return (CREATE);
	    if (strcmp (btokenp, "destroy") == EQUAL) return (DESTROY);
	    if (strcmp (btokenp, "load") == EQUAL) return (LOAD);
	    if (strcmp (btokenp, "print") == EQUAL) return (PRINT);
	    if (strcmp (btokenp, "sort") == EQUAL) return (SORT);
	    if (strcmp (btokenp, "quit") == EQUAL) return (QUIT);
	    if (strcmp (btokenp, "select") == EQUAL) return (SELECT);
	    if (strcmp (btokenp, "project") == EQUAL) return (PROJECT);
	    if (strcmp (btokenp, "join") == EQUAL) return (JOIN);
	    if (strcmp (btokenp, "insert") == EQUAL) return (INSERT);
	    if (strcmp (btokenp, "delete") == EQUAL) return (DELETE);
	    if (strcmp (btokenp, "intersect") == EQUAL) return (INTERSECT);
	    if (strcmp (btokenp, "union") == EQUAL) return (UNIONOP);
	    if (strcmp (btokenp, "on") == EQUAL) return (ON);
	    if (strcmp (btokenp, "key") == EQUAL) return (KEY);
	    if (strcmp (btokenp, "size") == EQUAL) return (SIZE);
	    if (strcmp (btokenp, "is") == EQUAL) return (IS);
	    if (strcmp (btokenp, "from") == EQUAL) return (FROM);
	    if (strcmp (btokenp, "into") == EQUAL) return (INTO);
	    if (strcmp (btokenp, "to") == EQUAL) return (TO);
	    if (strcmp (btokenp, "where") == EQUAL) return (WHERE);
	    if (strcmp (btokenp, "and") == EQUAL) return (AND);
	    if (strcmp (btokenp, "help") == EQUAL) return (HELP);
	    if (strcmp (btokenp, "buildindex") == EQUAL) return (BUILDINDEX);
	    if (strcmp (btokenp, "dropindex") == EQUAL) return (DROPINDEX);
	    if (strcmp (btokenp, "for") == EQUAL) return (FOR);
	    if (strcmp (btokenp, "") == EQUAL) return (ILLEGAL);

	    return (STR);
	}

} /* findtoken */


/* comment out the following code when you code the part 3 routines */
/*
insert (argc,argv)
int argc;
char **argv;
{
int i;
    printf("%s called with arguments:\n",argv[0]);
	for (i=1;i<argc;i++)
    printf("\t%s\n",argv[i]);
}

select (argc,argv)
int argc;
char **argv;
{
int i, j;
    printf("%s called with arguments:\n",argv[0]);
    printf("\t%s\n",argv[1]);
    printf("\t%s\n",argv[2]);

    for (j = 3; j < argc; j += 3) {
	printf("\t%s\n",argv[j]);
	i= *(int *)argv[j + 1];
	printf("\t%d\n",i);
	printf("\t%s\n",argv[j + 2]);
    }
}

project(argc,argv)
int argc;
char **argv;
{
int i;
    printf("%s called with arguments:\n",argv[0]);
	for (i=1;i<argc;i++)
    printf("\t%s\n",argv[i]);
}

delete(argc,argv)
int argc;
char **argv;
{
int i;
    printf("%s called with arguments:\n",argv[0]);
    printf("\t%s\n",argv[1]);
    printf("\t%s\n",argv[2]);
    i= *(int *)argv[3];
    printf("\t%d\n",i);
    printf("\t%s\n",argv[4]);
}

join(argc,argv)
int argc;
char **argv;
{
int i;
    printf("%s called with arguments:\n",argv[0]);
    printf("\t%s\n",argv[1]);
    printf("\t%s\n",argv[2]);
    printf("\t%s\n",argv[3]);
    printf("\t%s\n",argv[4]);
    printf("\t%s\n",argv[5]);
    i= *(int *)argv[6];
    printf("\t%d\n",i);
}

sort(argc,argv)
int argc;
char **argv;
{
int i;
    printf("Warning!  sort() is not implemented yet\n");
}

help(argc,argv)
int argc;
char **argv;
{
int i;
    printf("Warning!  help() is not implemented yet\n");
}
*/

/*
bcopy((char *) &tcode, ptr[scount], sizeof(int));
*/
