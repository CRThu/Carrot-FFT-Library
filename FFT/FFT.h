#pragma once

#ifndef _FFT_H_
#define _FFT_H_

#include "complex.h"

extern uint32_t FFT_PLOT;
extern uint32_t FFT_N;
extern uint8_t FFT_LOGN;

uint32_t FFT_Init(uint32_t fft_plot);
void InvertedArray(Complex* complexIn, Complex* complexOut);

#endif // _FFT_H_
