#ifndef FFT_H
#define FFT_H

#include <complex>
#include <iostream>

using std::complex;


typedef complex<double> Coeff;
typedef Coeff *Array;

void FFT(Array f, int M, Array buffer, int start = 0, int stride = 1);

void FFT_2D(Array *f, int M);

void iFFT(Array f, int M, Array buffer, int start = 0, int stride = 1);

void iFFT_2D(Array *f, int M);

void Trans(Array *f, int M);
#endif
