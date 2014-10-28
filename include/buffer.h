/*
 * buffer.h
 *
 *  Created on: 27-Oct-2014
 *      Author: nithin
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "defs.h"

typedef struct buffer{
    bool dirty;
    Page page;
}Buffer;

#endif /* BUFFER_H_ */
