/*
 * getnextrec.h
 *
 *  Created on: 30-Oct-2014
 *      Author: nithin
 */

#ifndef GETNEXTREC_H_
#define GETNEXTREC_H_

Rid getNextRid(short curPid, short curSlot, int recsPerPg, int numPgs, Rid lastRid);

int GetNextRec(const int relNum, const Rid *startRid, Rid *foundRid, char *recPtr);

#endif /* GETNEXTREC_H_ */
