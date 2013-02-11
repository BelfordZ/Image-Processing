#include "fft.h"
#include "pbmLib.h"

Array* PadImage(Array *f, int &h, int &w);
Array* MakeImgArray(int h, int w, tuple **array);
Array* MakeImgArray(int h, int w, Array *arr);
Array* MakeImgArray(int h, int w);
void PutComplexImageData(Array *complexImage, pbmLib imgObj, int M, char *fName);
void MotionBlurFilter(Array *F, Array *Ft, int M, float a, float b, float T);
void Mult(Array *F, Array *H, int M);

const double PI = acos(-1.0);

int main(int argc, char *argv[])
{
   float a = atof(argv[3]);
   float b = atof(argv[4]);
   float t = atof(argv[5]);
   cout << a <<"--" << b << "-------" << t <<endl;
   pbmLib img(argv[1]);
   int M = img.h;
   
   Array *myData = MakeImgArray(img.h, img.w, img.array);
   Array *myPaddedData = PadImage(myData, M, M);
   
   Trans(myPaddedData, M);
   FFT_2D(myPaddedData, M);

   Array *myDataCopy = MakeImgArray(M,M, myPaddedData);

   MotionBlurFilter(myDataCopy, myPaddedData, M, a, b, t);
   iFFT_2D(myPaddedData, M);
   Trans(myPaddedData, M);
   PutComplexImageData(myPaddedData, img, img.h, argv[2]);
}

void MotionBlurFilter(Array *F, Array *Ft, int M, float a, float b, float T)
{
   Coeff H;
   
   for(int u=0; u<M; u++)
   {
      for (int v=0; v<M; v++)
      {
	 float tmp = (PI*(((u-M/2) * a) + ((v-M/2) * b)));
	 Coeff y = Coeff(tmp, 0);

	 if ( tmp == 0 )
	 {
	    Coeff r = Coeff(T, 0);
	    H = r;
	 }
	 else
	 {
	    Coeff x = Coeff(0,1) * Coeff(-1,0);
	    H = (Coeff((T * sin(tmp)/tmp), 0)) * exp(x*y);
	 }
	 Ft[u][v] = H * F[u][v];
      }
   }
}

Array* PadImage(Array *f, int &h, int &w)
{
   double logH = ceil(log10(h) / log10(2));
      
   int newSizeH = pow(2,logH);
   int newSizeW = newSizeH;
    
   newSizeH = 2*newSizeH;
   newSizeW = 2*newSizeW;

   Array *myNewData = new Array[newSizeH];
   for(int i = 0; i<newSizeH; ++i)
   {
      myNewData[i] = new Coeff[newSizeW];
      for (int j=0; j<newSizeW; ++j)
      {
	 if (i >= h || j >= w)
	 {
	    myNewData[i][j] = Coeff(0,0);   
	 }
	 else
	 {
	    myNewData[i][j] = f[i][j];
	 }
      }
   }
   h = newSizeH;
   w = newSizeW;
   return myNewData;
}

Array* MakeImgArray(int h, int w, tuple **array)
{
   Array *tmp = new Array[h];
   for (int i=0; i<h; i++)
   {
      tmp[i] = new Coeff[w];
      for (int j=0; j<w; j++)
      {
	 tmp[i][j] = static_cast<double>(array[i][j][0]);
      }
   }
   return tmp;
}

Array* MakeImgArray(int h, int w, Array* arr)
{
   Array *tmp = new Array[h];
   for (int i=0; i<h; i++)
   {
      tmp[i] = new Coeff[w];
      for (int j=0; j<w; j++)
      {
	 tmp[i][j] = arr[i][j];
      }
   }
   return tmp;
}
Array* MakeImgArray(int h, int w)
{
   Array *tmp = new Array[h];
   for (int i=0; i<h; i++)
   {
      tmp[i] = new Coeff[w];
      for (int j=0; j<w; j++)
      {
	 tmp[i][j] = 0;
      }
   }
   return tmp;
}

void PutComplexImageData(Array *complexImage, pbmLib imgObj, int M, char *fName)
{
   imgObj.h = M;
   imgObj.w = M;
   for (int i=0; i<M; i++)
   {
      for (int j=0; j<M; j++)
      {
	 imgObj.array[i][j][0] = (complexImage[i][j].real() > 255) ? 255 : (complexImage[i][j].real() < 0) ? 0 : complexImage[i][j].real();
      }
   }
   imgObj << fName;
}
