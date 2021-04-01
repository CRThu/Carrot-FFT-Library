// FFT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>


// FFT N&LOGN CONFIG
#define N       65536
#define LOGN    16
// FFT GEN SINE WAVE
#define FS      0.05

#define PI      acos(-1.0)

typedef struct
{
    double Rez;
    double Imz;
}Complex;

Complex WNm[N]; // TODO : can be optimized

Complex CreateComplex(double Rez, double Imz)
{
    Complex newComplex = { Rez,Imz };
    return newComplex;
}

Complex AddComplex(Complex complexFFT, Complex complexB)
{
    complexFFT.Rez += complexB.Rez;
    complexFFT.Imz += complexB.Imz;
    return complexFFT;
}

Complex SubComplex(Complex complexFFT, Complex complexB)
{
    complexFFT.Rez -= complexB.Rez;
    complexFFT.Imz -= complexB.Imz;
    return complexFFT;
}

Complex MulComplex(Complex complexFFT, Complex complexB)
{
    Complex complexC = {
        complexFFT.Rez * complexB.Rez - complexFFT.Imz * complexB.Imz,
        complexFFT.Rez * complexB.Imz + complexFFT.Imz * complexB.Rez };
    return complexC;
}

double ModComplex(Complex complexIn)
{
    return sqrt(complexIn.Rez * complexIn.Rez + complexIn.Imz * complexIn.Imz);
}

void PrintComplex(Complex complexFFT)
{
    printf("%c%.6f%c%.6fi", complexFFT.Rez >= 0 ? '+' : '-', fabs(complexFFT.Rez),
        complexFFT.Imz >= 0 ? '+' : '-', fabs(complexFFT.Imz));
}

// b[n:0]->b[0:n]
void InvertedArray(Complex* complexIn, Complex* complexOut)
{
    uint8_t bits[LOGN];
    uint16_t i_calc;
    for (uint32_t i = 0; i < N; i++)
    {
        i_calc = i;
        for (uint16_t j = 0; j < LOGN; j++)
        {
            bits[j] = i_calc % 2;
            i_calc = i_calc / 2;
        }
        i_calc = 0;
        for (uint16_t j = 0; j < LOGN; j++)
        {
            i_calc += (uint16_t)pow(2, j) * bits[LOGN - 1 - j];
        }
        complexOut[i] = complexIn[i_calc];
        //printf("%d->%d\r\n",i, i_calc);
    }
}

// LUT
void GenWNm(void)
{
    for (uint32_t m = 0; m < N; m++)
    {
        WNm[m] = CreateComplex(cos((double)2.0 * PI * (double)m / (double)N),
            -sin((double)2.0 * PI * (double)m / (double)N));
    }
}

// TODO : can be optimized in loop[J]
void FFT(Complex* complexFFT)
{
    uint32_t B, P;
    Complex complexTmp;
    for (uint16_t L = 1; L <= LOGN; L++)                         // L = 1:M
    {
        B = pow(2, L - 1);                                      // B = 2^(L-1)
        for (uint32_t J = 0; J < B; J++)                        // j = 0:B-1
        {
            P = pow(2, LOGN - L) * J;                           // P = 2^(M-L)*J
            for (uint32_t K = J; K <= N - 1; K += pow(2, L))    // K = J:N-1:2^L
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
    for (uint32_t i = 0; i < N; i++)
    {
        sine[i] = sin((double)2.0 * PI * i * (double)fs);
    }
}


int main()
{
    double sine[N];
    Complex fft_in[N];
    Complex fft_calc[N];

    GenWNm();
    GenSine(sine, FS);
    for (int i = 0; i < N; i++)
        fft_in[i] = CreateComplex(sine[i], 0);

    clock_t t_start = clock();
    // FFT
    InvertedArray(fft_in, fft_calc);
    FFT(fft_calc);
    clock_t t_stop = clock();

    for (int i = 0; i < N; (N <= 256) ? (i++) : (i += N / 256))
    {
        printf("FFT N = %d : ", i);
        PrintComplex(fft_calc[i]);
        printf(", Mod : %.6f\n", ModComplex(fft_calc[i]));
    }

    double elapsedTime = ((double)t_stop - (double)t_start) / (double)CLOCKS_PER_SEC;
    printf("Calc FFT Elapsed Time : %.3lf second.\n", elapsedTime);


    return 0;
}