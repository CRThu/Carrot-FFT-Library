#pragma once

#ifndef _FFT_H_
#define _FFT_H_

#include <malloc.h>
#include "complex.h"

#define PI      acos(-1.0)

extern uint32_t FFT_N;
extern uint8_t FFT_LOGN;

extern Complex* pWNm;
extern uint32_t pWNmCnt;

uint32_t FFT_Init(uint32_t fft_num);
void FFT_DeInit();
void GenWNm(Complex* p);
Complex GetWNm(uint32_t index);
Complex PrintWNm();
void InvertedArray(Complex* complexArray);
void FFTCalc(Complex* complexFFT);

#endif // _FFT_H_
