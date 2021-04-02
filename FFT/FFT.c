#include "FFT.h"
#include <malloc.h>

#define PI      acos(-1.0)

// FFT CONFIG
uint32_t FFT_PLOT = 1024;
uint32_t FFT_N = 1024;
uint8_t FFT_LOGN = 10;

Complex* pWNm = (void*)0;

// LUT
Complex* GenWNm(void)
{
    Complex* p = &pWNm;
    pWNm = (Complex*)malloc(sizeof(Complex) * FFT_N);
    if (pWNm == NULL)
        return NULL;
    for (uint32_t m = 0; m < FFT_N; m++)
    {
        *p = CreateComplex(cos((double)2.0 * PI * (double)m / (double)FFT_N),
            -sin((double)2.0 * PI * (double)m / (double)FFT_N));
        printf("WNm[%d]=", m);
        PrintComplex(*p);
        printf("\r\n");
        p++;
    }
    return pWNm;
}

uint32_t FFT_Init(uint32_t fft_plot)
{
    FFT_PLOT = fft_plot;
    FFT_LOGN = (uint8_t)ceil(log2(FFT_PLOT));
    FFT_N = (uint32_t)pow(2, FFT_LOGN);
    GenWNm();
    return FFT_N;
}

void FFT_DeInit()
{
    free(pWNm);
    pWNm = NULL;
}

// b[n:0]->b[0:n]
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