/*
 * deleterec.h
 *
 *  Created on: 31-Oct-2014
 *      Author: nithin
 */

#ifndef DELETEREC_H_
#define DELETEREC_H_

#include <stdio.h>
#include "globals.h"
#include "readpage.h"
#include "error.h"

int DeleteRec(const int relNum, const Rid *rid);

#endif /* DELETEREC_H_ *
