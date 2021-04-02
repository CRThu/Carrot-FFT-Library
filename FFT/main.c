
#include <time.h>

#include "complex.h"

// FFT GEN SINE WAVE
#define FS      0.05



/*
// TODO : can be optimized in loop[J]
void FFTCalc(Complex* complexFFT)
{
    uint32_t B, P;
    Complex complexTmp;
    for (uint16_t L = 1; L <= FFT_LOGN; L++)                         // L = 1:M
    {
        B = pow(2, L - 1);                                      // B = 2^(L-1)
        for (uint32_t J = 0; J < B; J++)                        // j = 0:B-1
        {
            P = pow(2, FFT_LOGN - L) * J;                           // P = 2^(M-L)*J
            for (uint32_t K = J; K <= FFT_N - 1; K += pow(2, L))    // K = J:N-1:2^L
            {
                complexTmp = AddComplex(complexFFT[K], MulComplex(complexFFT[K + B], WNm[P]));
                complexFFT[K + B] = SubComplex(complexFFT[K], MulComplex(complexFFT[K + B], WNm[P]));
                complexFFT[K] = complexTmp;
            }
        }
    }
}

// Sine
void GenSine(double* sine, double fs)
{
    for (uint32_t i = 0; i < FFT_N; i++)
    {
        sine[i] = sin((double)2.0 * PI * i * (double)fs);
    }
}


int main()
{
    double sine[FFT_N];
    Complex fft_in[FFT_N];
    Complex fft_calc[FFT_N];

    GenWNm();
    GenSine(sine, FS);
    for (int i = 0; i < FFT_N; i++)
        fft_in[i] = CreateComplex(sine[i], 0);

    clock_t t_start = clock();
    // FFT
    InvertedArray(fft_in, fft_calc);
    FFTCalc(fft_calc);
    clock_t t_stop = clock();

    for (int i = 0; i < FFT_N; (FFT_N <= 256) ? (i++) : (i += FFT_N / 256))
    {
        printf("FFT N = %d : ", i);
        PrintComplex(fft_calc[i]);
        printf(", Mod : %.6f\n", ModComplex(fft_calc[i]));
    }

    double elapsedTime = ((double)t_stop - (double)t_start) / (double)CLOCKS_PER_SEC;
    printf("Calc FFT Elapsed Time : %.3lf second.\n", elapsedTime);

    return 0;
}

*/



int main()
{
    FFT_Init(64);
    FFT_DeInit();
}