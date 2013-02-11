#include <cmath>
#include <algorithm>
#include <functional>
#include "fft.h"

using namespace std;

const double PI = acos(-1.0);
void Trans(Array *f, int M)
{
   for (int i=0; i<M; i++)
   {
      for(int j=0; j<M; j++)
      {
	 double tmp = i+j;
	 double temp = pow(-1, tmp);
	 Coeff x = temp;
	 f[i][j] *= x;
      }
   }
}
void FFT_2D(Array *f, int M)
{
   int start = 0;
   int stride = 1;
   
   Array f2 = new Coeff[M];
   Array buf;
 
   for (int col=0; col<M; col++)
   {
      buf = new Coeff[M];
      for(int row=0; row<M; row++)
      {
	 f2[row] = f[row][col];
      }
      FFT(f2, M, buf, start, stride);
      for (int row=0; row<M; row++)
      {
	 f[row][col] = f2[row];
      }
      delete[] buf;
   }
  
   for (int row=0; row<M; row++)
   {
      buf = new Coeff[M];
      for(int col=0; col<M; col++)
      {
	 f2[col] = f[row][col];
      }
      FFT(f2, M, buf, start, stride);
      for(int col=0; col<M; col++)
      {
	 f[row][col] = f2[col];
      }
      delete[] buf;
   }
}

void FFT(Array f, int M, Array buffer, int start, int stride)
{
  if (M == 1) {
    return;
  }
   
  // recursively compute the odd and even part
  int K = M/2;
  FFT(f, K, buffer, start, 2*stride);                 // even part
  FFT(f, K, buffer, start + stride, 2*stride);        // odd part

  Coeff omega = exp(Coeff(0, -2*PI/M));
  int ei = start, oi = start + stride;
  Coeff power = 1;
  for (int u = 0; u < K; u++) {
    buffer[u] = f[ei] + f[oi] * power;
    buffer[u+K] = f[ei] - f[oi] * power;
    ei += 2*stride;
    oi += 2*stride;
    power *= omega;
  }

  int i = start;
  for (int u = 0; u < M; u++) {
    f[i] = buffer[u];
    i += stride;
  }
}
void iFFT_2D(Array *f, int M)
{
   int start = 0;
   int stride = 1;
   
   Array f2 = new Coeff[M];
   Array buf = new Coeff[M];
   
   for (int row=0; row<M; row++)
   {
      for(int col=0; col<M; col++)
      {
	 f2[col] = f[row][col];
      }
      iFFT(f2, M, buf, start, stride);
      
      for (int col=0; col<M; col++)
      {
	 f[row][col] = f2[col];
      }
   }
   for (int col=0; col<M; col++)
   {
      for(int row=0; row<M; row++)
      {
	 f2[row] = f[row][col];
      }
      
      iFFT(f2, M, buf, start, stride);
      
      for(int row=0; row<M; row++)
      {
	 f[row][col] = f2[row];
	 //Coeff argg = (M*M);
	 //f[row][col] /= argg;
      }
   }
}

void iFFT(Array f, int M, Array buffer, int start, int stride)
{   
   int index = start;
   for (int i = 0; i < M; i++) {
      f[index] = conj(f[index]);
      index += stride;
   }
   FFT(f, M, buffer, start, stride);
   
   index = start;
   for (int i = 0; i < M; i++) {
      f[index] = conj(f[index])/Coeff(M);
      index += stride;
   }
}

