﻿#include "FFT.h"

// FFT CONFIG
uint32_t FFT_N = 0;
uint8_t FFT_LOGN = 0;

Complex* pWNm = (void*)0;

uint32_t FFT_Init(uint32_t fft_num)
{
    // CALC FFT CONFIG
    FFT_LOGN = (uint8_t)ceil(log2(fft_num));
    FFT_N = (uint32_t)pow(2, FFT_LOGN);

    // MALLOC
    pWNm = (Complex*)malloc(sizeof(Complex) * FFT_N);
    if (pWNm == NULL)
        return NULL;

    GenWNm(pWNm);

    return FFT_N;
}

void FFT_DeInit()
{
    free(pWNm);
    pWNm = NULL;
}

void GenWNm(Complex* p)
{
    for (uint32_t m = 0; m < FFT_N; m++)
    {
        *p = CreateComplex(cos((double)2.0 * PI * (double)m / (double)FFT_N),
            -sin((double)2.0 * PI * (double)m / (double)FFT_N));
        //printf("WNm[%d]=", m);
        //PrintComplex(*p);
        //printf("\r\n");
        p++;
    }
}

// b[n:0]->b[0:n]
void InvertedArray(Complex* complexArray)
{
    uint32_t k = 0;
    uint32_t j = 0;
    for (uint32_t i = 0; i < FFT_N - 1; i++)
    {
        if (i < j)
        {
            SwapComplex(&complexArray[i], &complexArray[j]);
            //printf("INV_CVT:%d->%d\n", i, j);
        }
        // K = 100..00
        k = FFT_N / 2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        j += k;
    }
}

/*
// Old Inverted Array
void InvertedArray(Complex* complexIn, Complex* complexOut)
{
    uint32_t index_o_calc;
    uint32_t index_i;
    for (uint32_t index_o = 0; index_o < FFT_N; index_o++)
    {
        index_o_calc = index_o;
        index_i = 0;
        for (uint8_t j = 0; j < FFT_LOGN; j++)
        {
            index_i = (index_i << 1) | (index_o_calc & 1);
            index_o_calc >>= 1;
        }
        complexOut[index_o] = complexIn[index_i];
        //printf("%d->%d\r\n", index_o, index_i);
    }
}
*/

// TODO : can be optimized in loop[J]
void FFTCalc(Complex* complexFFT)
{
    uint32_t B, P;
    Complex complexTmp;
    for (uint16_t L = 1; L <= FFT_LOGN; L++)                    // L = 1:M
    {
        B = pow(2, L - 1);                                      // B = 2^(L-1)
        for (uint32_t J = 0; J < B; J++)                        // j = 0:B-1
        {
            P = pow(2, FFT_LOGN - L) * J;                           // P = 2^(M-L)*J
            for (uint32_t K = J; K <= FFT_N - 1; K += pow(2, L))    // K = J:N-1:2^L
            {
                complexTmp = AddComplex(complexFFT[K], MulComplex(complexFFT[K + B], pWNm[P]));
                complexFFT[K + B] = SubComplex(complexFFT[K], MulComplex(complexFFT[K + B], pWNm[P]));
                complexFFT[K] = complexTmp;
            }
        }
    }
}