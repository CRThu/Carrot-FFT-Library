#include "complex.h"

Complex CreateComplex(double Rez, double Imz)
{
    Complex ComplexA = { Rez,Imz };
    return ComplexA;
}

Complex AddComplex(Complex complexA, Complex complexB)
{
    complexA.Rez += complexB.Rez;
    complexA.Imz += complexB.Imz;
    return complexA;
}

Complex SubComplex(Complex complexA, Complex complexB)
{
    complexA.Rez -= complexB.Rez;
    complexA.Imz -= complexB.Imz;
    return complexA;
}

Complex MulComplex(Complex complexA, Complex complexB)
{
    Complex complexC = {
        complexA.Rez * complexB.Rez - complexA.Imz * complexB.Imz,
        complexA.Rez * complexB.Imz + complexA.Imz * complexB.Rez };
    return complexC;
}

Complex ConjComplex(Complex complexA)
{
    complexA.Imz = -complexA.Imz;
    return complexA;
}

double ModComplex(Complex complexA)
{
    return sqrt(complexA.Rez * complexA.Rez + complexA.Imz * complexA.Imz);
}

void SwapComplex(Complex* complexA, Complex* complexB)
{
    Complex complexSwap;
    memcpy(&complexSwap, (void*)complexA, sizeof(complexSwap));
    memcpy((void*)complexA, (void*)complexB, sizeof(complexSwap));
    memcpy((void*)complexB, &complexSwap, sizeof(complexSwap));
}

void PrintComplex(Complex complexA)
{
    printf("%c%.6f%c%.6fj", complexA.Rez >= 0 ? '+' : '-', fabs(complexA.Rez),
        complexA.Imz >= 0 ? '+' : '-', fabs(complexA.Imz));
}