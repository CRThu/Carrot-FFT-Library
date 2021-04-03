#pragma once

#ifndef _FFT_H_
#define _FFT_H_

#include <malloc.h>
#include "complex.h"

#define PI      acos(-1.0)

extern uint32_t FFT_N;
extern uint8_t FFT_LOGN;

uint32_t FFT_Init(uint32_t fft_num);
void FFT_DeInit();
void GenWNm(Complex* p);
void InvertedArray(Complex* complexIn, Complex* complexOut);
void FFTCalc(Complex* complexFFT);

#endif // _FFT_H_
