/*
 * helpers.h
 *
 *  Created on: 30-Oct-2014
 *      Author: nithin
 */

#ifndef HELPERS_H_
#define HELPERS_H_

void readStringFromByteArray(char * string, const char *byteArray, const int offset, const int size);

int readIntFromByteArray(const char *byteArray, const int offset);

float readFloatFromByteArray(const char* byteArray, const int offset);

bool compareNum(float val1, float val2, int compOp);

bool compareStrings(char *s1, char *s2, int compOp);

void convertIntToByteArray(int value, char *byteArray);

Rid getLastRid(int relNum);

#endif /* HELPERS_H_ */
