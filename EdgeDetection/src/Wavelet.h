/*
 * Wavelet.h
 *
 *  Created on: Oct 19, 2017
 *      Author: marco
 */

#ifndef WAVELET_H_
#define WAVELET_H_

#include"OpenCVLibrary.h"

void dhwt1dRow(uchar* src, uchar* output, int size);

void dhwt1dColumn(uchar* src, uchar* output, int size);

void dhwt2d(int, void *);

void copyArray(uchar* src, uchar* dst, int length);
#endif /* WAVELET_H_ */
