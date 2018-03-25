/*
 * ColorReduce.h
 *
 *  Created on: Oct 19, 2017
 *      Author: marco
 */

#ifndef COLORREDUCE_H_
#define COLORREDUCE_H_
#include"OpenCVLibrary.h"

extern Mat final_pic;
void colorReduce(int, void *);


/*
 * note the order is blue green red
 */
void removeColor(int, void *);

#endif /* COLORREDUCE_H_ */
