/*
 * select.c
 *
 *  Created on: 7-Oct-2014
 *      Author: Dheeraj
 */

 #include "../include/select.h"

/*
 * Function:  Select() 
 * ------------------------
 * implements relational selection command
 *
 * argv[0] = “select”
 * argv[1] = result relation
 * argv[2] = source relation
 * argv[3] = attribute name
 * argv[4] = operator
 * argv[5] = value
 * argv[argc] = NIL
 *  
 *  returns: OK upon successfully performed selection
 *           NOTOK: otherwise
 */

int Select (int argc, char **argv)
{
    int relNum, new_relNum, numAttrs, count, i, ret_val, offset, attr_found_flag = 0;
    int attrSize, int_val;
    float float_val;
    struct attrCatalog* head;
    datatype type;
    Rid startRid = {1,0}, *foundRid;
    char **argument_list, *recPtr;

    if(argc < 6)
        return ErrorMsgs(ARGC_INSUFFICIENT,g_print_flag);

    if(OpenRel(argv[2]) == NOTOK)
        return ErrorMsgs(RELNOEXIST, g_print_flag);
    /* Finding the relNum of Source Relation */
    relNum = FindRelNum(argv[2]);

    head = g_catcache[relNum].attrList;
    numAttrs = g_catcache[relNum].numAttrs;

    /* Preparing Argument list which should be passed to Create() */
    argument_list = malloc(sizeof(char*) * (numAttrs+1)*2 );
    argument_list[0] = malloc(sizeof(char) * RELNAME);
    argument_list[1] = malloc(sizeof(char) * RELNAME);

    for(count=2; count < (numAttrs+1)*2; count++){
        argument_list[count] = malloc(sizeof(char) * RELNAME);
        argument_list[count+1] = malloc(sizeof(char) * 4);
    }

    strcpy(argument_list[0], "create");
    strcpy(argument_list[1], argv[1]);
    count = 2;
    while(head != NULL){
        strcpy(argument_list[count],head->attrName);
        switch(head->type){
            case INTEGER: strcpy(argument_list[count+1],"i");
                break;
            case STRING: sprintf(argument_list[count+1], "s%d", head->length);
                break;
            case FLOAT: strcpy(argument_list[count+1],"f");
                break; 
        }
        /* This is to catch the desired attribute's specifications from Source relation. 
        Expected to happen only once in this loop */
        if(strcmp(head->attrName, argv[3]) == 0){
            attr_found_flag = 1;
            offset = head -> offset;
            type = head -> type;
            attrSize = head -> length;
        }
        head = head->next;
        count = count + 2;
    }
    /* Given attribute name never appeared in attr linkedlist */
    if(attr_found_flag == 0)
        ErrorMsgs(ATTRNOEXIST,g_print_flag);

    ret_val = Create( (numAttrs+1)*2, argument_list );

    for(i=0; i<(numAttrs+1)*2; i++)
        free(argument_list[i]);
    free(argument_list);

    if(ret_val == NOTOK)
        return NOTOK;

    OpenRel(argv[1]);
    new_relNum = FindRelNum(argv[1]);

    switch(type){
        case STRING:
            removeQuotes(argv[5]);
            break;
        case INTEGER: 
            int_val = atoi(argv[5]);
            convertIntToByteArray(int_val,argv[5]);
            break;
        case FLOAT:
            float_val = atof(argv[5]);
            convertFloatToByteArray(float_val, argv[5]);
            break;
    }
    /* Finding record from Source, which satisfying given condition, and Adding to Result Relation*/
    while( FindRec(relNum, &startRid, &foundRid, &recPtr, type, attrSize, 
                        offset, argv[5], atoi(argv[4])) == OK ){
        InsertRec(new_relNum, recPtr);
        startRid = (*foundRid);
        free(foundRid);
    }
    return OK;
}
