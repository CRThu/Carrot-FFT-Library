#pragma once
#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct Complex
{
    double Rez;
    double Imz;
}Complex;

Complex CreateComplex(double Rez, double Imz);
Complex AddComplex(Complex complexFFT, Complex complexB);
Complex SubComplex(Complex complexFFT, Complex complexB);
Complex MulComplex(Complex complexFFT, Complex complexB);
double ModComplex(Complex complexIn);
void PrintComplex(Complex complexFFT);

#endif // _COMPLEX_H_
