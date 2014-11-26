/*
 * readpage.h
 *
 *  Created on: 29-Oct-2014
 *      Author: nithin
 */

#ifndef READPAGE_H_
#define READPAGE_H_

#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include "globals.h"
#include "error.h"
#include "readpage.h"
#include "flushpage.h"
#include "readpage.h"
#include "helpers.h"

int ReadPage(int relNum, short pid);

#endif /* READPAGE_H_ */
