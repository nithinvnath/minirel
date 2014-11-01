/*
 * insertrec.h
 *
 *  Created on: 31-Oct-2014
 *      Author: nithin
 */

#ifndef INSERTREC_H_
#define INSERTREC_H_

#include <stdio.h>

#include "globals.h"
#include "readpage.h"
#include "getnextrec.h"
#include "helpers.h"
#include "error.h"

int InsertRec(const int relNum, const char*recPtr);

int getNextFreeSlot(const int relNum, const Rid startRid, Rid *foundRid);

#endif /* INSERTREC_H_ */

