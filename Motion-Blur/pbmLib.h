#ifndef PBMLIB_H
#define PBMLIB_H

#include <pam.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

class pbmLib
{
  private:
   pam pam_struct;
   char *fname;
   
   bool read_image(char *filename);
   bool write_image(char *filename);
   
  public:
   tuple **array;
   int h, w;
   
   pbmLib();
   pbmLib(const pbmLib &cpy);
   pbmLib(char *filename);
   ~pbmLib();

   pbmLib& operator =(const pbmLib& other);
   pbmLib operator +(const pbmLib& other);
   pbmLib operator -(const pbmLib& other);
   void operator <<(char *fname);   
};

#endif
