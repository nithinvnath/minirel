/*
 * flushpage.h
 *
 *  Created on: 29-Oct-2014
 *      Author: nithin
 */

#ifndef FLUSHPAGE_H_
#define FLUSHPAGE_H_

#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include "globals.h"
#include "error.h"
#include "helpers.h"

int FlushPage(int relNum);

#endif /* FLUSHPAGE_H_ */
