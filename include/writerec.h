/*
 * writerec.h
 *
 *  Created on: 31-Oct-2014
 *      Author: nithin
 */

#ifndef WRITEREC_H_
#define WRITEREC_H_

#include <stdio.h>
#include "globals.h"
#include "readpage.h"
#include "error.h"

int WriteRec(const int relNum, const char *recPtr,const Rid *RecId);

#endif /* WRITEREC_H_ */
