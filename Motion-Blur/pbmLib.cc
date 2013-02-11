#include "pbmLib.h"

pbmLib::pbmLib()
{
}
pbmLib::pbmLib(char *filename)
{
   read_image(filename);
   h = pam_struct.height;
   w = pam_struct.width;
}
pbmLib::pbmLib(const pbmLib &cpy)
{
   pam_struct = cpy.pam_struct;
   h = cpy.h;
   w = cpy.w;
   fname = cpy.fname;
   
   read_image(cpy.fname);
   
   for (int i=0; i<cpy.h; i++)
   {
      for (int j=0; j<cpy.w; j++)
      {
	 array[i][j][0] = cpy.array[i][j][0];	 
      }
   }
}
pbmLib::~pbmLib()
{
}
pbmLib& pbmLib::operator =(const pbmLib& cpy)
{
   pam_struct = cpy.pam_struct;
   h = cpy.h;
   w = cpy.w;
   fname = cpy.fname;
   
   for (int i=0; i<cpy.h; i++)
   {
      for (int j=0; j<cpy.w; j++)
      {
	 array[i][j][0] = cpy.array[i][j][0];
      }
   }
   return *this;
}
pbmLib pbmLib::operator -(const pbmLib& other)
{
   pbmLib result = other;
   cout << other.array[56][52][0] << "=" << result.array[56][52][0]<<endl;
   for (int i=0; i<other.h; i++)
   {
      for (int j=0; j<other.w; j++)
      {
	 result.array[i][j][0] = array[i][j][0] - other.array[i][j][0];
      }
   }
   return result;  
}
pbmLib pbmLib::operator +(const pbmLib& other)
{
   pbmLib result = other;

   for (int i=0; i<other.h; i++)
   {
      for (int j=0; j<other.w; j++)
      {
	 result.array[i][j][0] = array[i][j][0] + other.array[i][j][0];
      }
   }
   return result;  
}
void pbmLib::operator <<(char *fname)
{
   this->write_image(fname);
}
bool pbmLib::read_image(char *filename)
{
   fname = filename;
   FILE *f;

   if ((f = pm_openr(filename)) == NULL)
   {
      return false;
   }
   if ((array = pnm_readpam(f, &pam_struct, PAM_STRUCT_SIZE(tuple_type))) == NULL)
   {
      return false;
   }
   pm_close(f);
   return true;
}
bool pbmLib::write_image(char *filename)
{
   FILE *f;

   if ((f = pm_openw(filename)) == NULL)
   {
      cerr << "Cannot open file \"" << filename << "\" for writing." << endl;
      return false;
   }

   pam_struct.file = f;
  
   pnm_writepam(&pam_struct, array);

   pm_close(f);
   return true;
}
