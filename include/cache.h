/*
 * cache.h
 *
 *  Created on: 27-Oct-2014
 *      Author: nithin
 */

#ifndef CACHE_H_
#define CACHE_H_

#include "defs.h"

/* Attribute catalog structure*/
struct attrCatalog {
    unsigned short offset;      //offset of attribute within record
    unsigned short length;      //length of attribute
    datatype type;              //attribute type: i, f, or s
    char attrName[RELNAME];     //name of attribute
    char relName[RELNAME];      //name of relation

    struct attrCatalog *next;   //Pointer to next
};

/* Relation cache structure */
typedef struct relCache {
    char relName[RELNAME];      //Relation name
    unsigned short recLength;   //record length
    unsigned short recsPerPg;   //records per page
    unsigned short numAttrs;    //number of attributes
    unsigned int numRecs;       //total number of records
    unsigned int numPgs;        //total number of pages

    Rid relcatRid;                  //RID
    int relFile;                    //File descriptor for the open relation
    bool dirty;                     //True if record on disk is out-dated
    struct attrCatalog* attrList;   //Linked list of attribute descriptors
} CacheEntry;

#endif /* CACHE_H_ */
