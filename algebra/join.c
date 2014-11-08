/*
 * join.c
 *
 *  Created on: 7-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/join.h"

/*
 * Function:  copy_binary_array() 
 * ------------------------------
 * copies binary array from source to destination.
 *
 * dest : destination array
 * source: source array
 * length: length of the array
 */

void copy_binary_array(char *dest, char *source, int length){
    int i;
    for (i = 0; i < length; ++i){
        dest[i] = source[i];
    }
}

/*
 * Function:  Join() 
 * ------------------------
 * implements natural join
 *
 * argv[0] = “join”
 * argv[1] = result relation
 * argv[2] = source relation 1
 * argv[3] = attribute name 1
 * argv[4] = source relation 2
 * argv[5] = attribute name 2
 * argv[argc] = NIL
 *  
 *  returns: OK upon successfully performed join relation
 *           NOTOK: otherwise
 */

int Join (int argc, char **argv)
{
    int relNum1, relNum2, count, attr_found_flag = 0, i, ret_val, rec_result_len;
    int num_attrs_rel1, num_attrs_rel2, num_attrs_total;
    int offset1, offset2, attrSize1, attrSize2, new_relNum;
    datatype type1, type2;
    struct attrCatalog *head;
    char **argument_list, *recPtr1, *recPtr2, *recResult;
    Rid start_rel1 = {1,0} , start_rel2 = {1,0}, *found_rel1, *found_rel2;

    if(argc < 6)
        return ErrorMsgs(ARGC_INSUFFICIENT,g_print_flag);

    if( (relNum1 = OpenRel(argv[2])) == NOTOK || (relNum2 = OpenRel(argv[4])) == NOTOK)
        return NOTOK;

    num_attrs_rel1 = g_catcache[relNum1].numAttrs;
    num_attrs_rel2 = g_catcache[relNum2].numAttrs;
    num_attrs_total = num_attrs_rel1 + num_attrs_rel2;

    /* Preparing Argument list which should be passed to Create() */
    argument_list = malloc(sizeof(char*) * (num_attrs_total*2) );
    argument_list[0] = malloc(sizeof(char) * RELNAME);
    argument_list[1] = malloc(sizeof(char) * RELNAME);

    for(count=2; count < num_attrs_total*2; count++){
        argument_list[count] = malloc(sizeof(char) * RELNAME);
        argument_list[count+1] = malloc(sizeof(char) * 4);
    }

    strcpy(argument_list[0], "create");
    strcpy(argument_list[1], argv[1]);

    count = 2;
    head = g_catcache[relNum1].attrList;

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
        if(strcmp(head->attrName, argv[3]) == 0){
            attr_found_flag = 1;
            offset1 = head -> offset;
            type1 = head -> type;
            attrSize1 = head -> length;
        }
        head = head->next;
        count++;
    }
    if(attr_found_flag == 0)
        ErrorMsgs(ATTRNOEXIST,g_print_flag);

    /* Next Relation's attribute list */
    attr_found_flag = 0;
    head = g_catcache[relNum2].attrList;

    while(head != NULL){
        /* Skipping the join attribute in 2nd relation */
        if(strcmp(head->attrName,argv[5]) == 0){
            head = head->next;
            continue;
        }
        strcpy(argument_list[count],head->attrName);
        /* This is to give different name for same attribute names in two Relations */
        for(i=2; i<num_attrs_rel1+2; i=i+2)
            if(strcmp(argument_list[i],head->attrName) == 0){
                strcat(argument_list[count], "_2");
            }

        switch(head->type){
            case INTEGER: strcpy(argument_list[count+1],"i");
                break;
            case STRING: sprintf(argument_list[count+1], "s%d", head->length);
                break;
            case FLOAT: strcpy(argument_list[count+1],"f");
                break; 
        }
        if(strcmp(head->attrName, argv[5]) == 0){
            attr_found_flag = 1;
            offset2 = head -> offset;
            type2 = head -> type;
            attrSize2 = head -> length;
        }
        head = head->next;
        count++;
    }
    if(attr_found_flag == 0)
        ErrorMsgs(ATTRNOEXIST,g_print_flag);

    ret_val = Create( num_attrs_total - 1, argument_list );
    OpenRel(argv[1]);
    int new_relNum = FindRelNum(argv[1]);

    for(i = 0; i < num_attrs_total*2; i++)
        free(argument_list[i]);
    free(argument_list);

    if(ret_val == NOTOK)
        return NOTOK;

    if(type1 != type2)
        return ErrorMsgs(TYPE_MISMATCH, g_print_flag);

    rec_result_len = g_catcache[relNum1].recLength + g_catcache[relNum2].recLength - attrSize2;
    recResult = malloc(sizeof(char)* (rec_result_len) );

    while(GetNextRec(relNum1, &start_rel1, &found_rel1, &recPtr1) == OK){
        while(FindRec(relNum2, &start_rel2, &found_rel2, &recPtr2, type2, attrSize2, offset2,
            recPtr1 + offset1, EQ)){

            copy_binary_array(recResult, recPtr1, g_catcache[relNum1].recLength);
            copy_binary_array(recResult + g_catcache[relNum1].recLength, recPtr2, offset2);
            copy_binary_array(recResult + g_catcache[relNum1].recLength + offset2,
                recPtr2 + offset2 + attrSize2, g_catcache[relNum2].recLength - offset2 - attrSize2);

            InsertRec(new_relNum, recResult);

            start_rel2 = *found_rel2;
            free(found_rel2);
        }
        start_rel1 = *found_rel1;
        free(found_rel1);
    }

    return OK;
}
