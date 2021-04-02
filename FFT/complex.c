#include "complex.h"

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
    printf("%c%.6f%c%.6fj", complexFFT.Rez >= 0 ? '+' : '-', fabs(complexFFT.Rez),
        complexFFT.Imz >= 0 ? '+' : '-', fabs(complexFFT.Imz));
}