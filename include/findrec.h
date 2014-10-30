/*
 * findrec.h
 *
 *  Created on: 31-Oct-2014
 *      Author: nithin
 */

#ifndef FINDREC_H_
#define FINDREC_H_

int FindRec(int relNum, const Rid *startRid, Rid *foundRid, char *recPtr, const char attrType,
        const int attrSize, const int attrOffset, const char *valuePtr, const int compOp);

#endif /* FINDREC_H_ */
