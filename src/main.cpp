#include <windows.h>
#include <iostream>
#include "randomTests.h"

typedef int (__cdecl *MYPROC)(int, int); 

int main(int argc, char *argv[])
{
   int a = 1;
   HINSTANCE hinstLib = LoadLibrary(TEXT("..\\myDynamicLib\\Debug\\myDynamicLib.dll"));

    if (hinstLib != NULL) 
    {
      std::cout << "namerihme dll-a\n";
      MYPROC ProcMult = (MYPROC) GetProcAddress(hinstLib, "multiply"); 
 
      if (NULL != ProcMult) 
      {
         std::cout << "funkciqta i neq\n";
         a = (ProcMult)(7,14); 
      }
      // Free the DLL module.
 
      FreeLibrary(hinstLib); 
    } 


   Tosho t(42);

   std::cout << "tosho is " << t.b << " 3+4=" << sum(3,4) << " 3 ravno li e na 3 = " << equals(3,3) << " 7*14=" << a <<std::endl;
   return 0;
}