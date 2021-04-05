#pragma once
#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

typedef struct Complex
{
    double Rez;
    double Imz;
}Complex;

Complex CreateComplex(double Rez, double Imz);
Complex AddComplex(Complex complexA, Complex complexB);
Complex SubComplex(Complex complexA, Complex complexB);
Complex MulComplex(Complex complexA, Complex complexB); 
Complex ConjComplex(Complex complexA);
double ModComplex(Complex complexA);
void SwapComplex(Complex* complexA, Complex* complexB);
void PrintComplex(Complex complexA);

#endif // _COMPLEX_H_
