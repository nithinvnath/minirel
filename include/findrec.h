/*
 * findrec.h
 *
 *  Created on: 31-Oct-2014
 *      Author: nithin
 */

#ifndef FINDREC_H_
#define FINDREC_H_

#include <stdlib.h>

#include "../include/globals.h"
#include "../include/error.h"
#include "../include/getnextrec.h"
#include "../include/findrec.h"
#include "../include/helpers.h"
#include "../include/readpage.h"

int FindRec(int relNum, Rid *startRid, Rid **foundRid, char **recPtr, const char attrType,
        const int attrSize, const int attrOffset, const char *valuePtr, const int compOp);

#endif /* FINDREC_H_ */
