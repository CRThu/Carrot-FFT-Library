
#include <time.h>
#include <string.h>
#include <windows.h>
#include <psapi.h>
#pragma  comment(lib,"Psapi.lib")

#include "complex.h"
#include "FFT.h"


// DEFINE
#define SAMPLE_CNT          1048576
#define SINE_FS             0.05

// TESTBENCH
//#define VERIFY_TESTBENCH    8
#define SPEED_TESTBENCH     1048576*256

// Sine
void GenSine(double* sine, double fs, double cnt)
{
    for (uint32_t i = 0; i < cnt; i++)
    {
        sine[i] = sin((double)2.0 * PI * (double)i * (double)fs);
    }
}

int main()
{
    int iter = 1;
    int fft_sample_cnt = SAMPLE_CNT;
#if SPEED_TESTBENCH != 0
    iter = (int)ceil(log2(SPEED_TESTBENCH));
    fft_sample_cnt = 2;
#endif
    printf("CARROT-FFT-LIBRARY TESTBENCH @ https://github.com/CRThu \n");

    printf("\n");
    printf("|\tFFT N |\tINIT Elapsed |\tCALC Elapsed |\tMemory Usage |\n");
    printf("|\t----- |\t------------ |\t------------ |\t------------ |\n");

    for (int i = 0; i < iter; i++)
    {
        clock_t t_start;
        clock_t t_stop;
        double elapsedTime;

        // INIT
        t_start = clock();
        FFT_Init(fft_sample_cnt);
        t_stop = clock();
        elapsedTime = ((double)t_stop - (double)t_start) / (double)CLOCKS_PER_SEC;
        printf("|%12d |\t%10.3lf s |", FFT_N, elapsedTime);

        // MALLOC
        double* sine = NULL;
        sine = (double*)malloc(sizeof(double) * FFT_N);
        if (sine == NULL)
            return -1;
        memset(sine, 0, sizeof(double) * FFT_N);

        Complex* fft_in = NULL;
        fft_in = (Complex*)malloc(sizeof(Complex) * FFT_N);
        if (fft_in == NULL)
            return -1;
        memset(fft_in, 0, sizeof(Complex) * FFT_N);

        Complex* fft_out = NULL;
        fft_out = (Complex*)malloc(sizeof(Complex) * FFT_N);
        if (fft_out == NULL)
            return -1;
        memset(fft_out, 0, sizeof(Complex) * FFT_N);

        // GEN SINE WAVE
        GenSine(sine, SINE_FS, fft_sample_cnt);
        for (uint32_t i = 0; i < FFT_N; i++)
            fft_in[i] = CreateComplex(sine[i], 0);

        // FFT CALC
        t_start = clock();
        InvertedArray(fft_in, fft_out);
        FFTCalc(fft_out);
        t_stop = clock();
        elapsedTime = ((double)t_stop - (double)t_start) / (double)CLOCKS_PER_SEC;

        HANDLE handle = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS pmc;
        GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));

        printf("\t%10.3lf s |\t%9d KB |\n", elapsedTime, pmc.WorkingSetSize/1024);

#if VERIFY_TESTBENCH != 0
        for (uint32_t i = 0; i < FFT_N; (FFT_N <= VERIFY_TESTBENCH) ? (i++) : (i += FFT_N / VERIFY_TESTBENCH))
        {
            printf("FFT k = %8d;\tX(k) = ", i);
            PrintComplex(fft_out[i]);
            printf(" (Mod = %.6f)\n", ModComplex(fft_out[i]));
        }
#endif
        // FREE
        FFT_DeInit();
        free(sine);
        free(fft_in);
        free(fft_out);
        sine = NULL;
        fft_in = NULL;
        fft_out = NULL;

#if SPEED_TESTBENCH != 0
        fft_sample_cnt *= 2;
#endif
    }
    return 0;
}