#include <iostream>
#include "randomTests.h"


typedef int (__cdecl *MYPROC)(int, int); 

int main(int argc, char *argv[])
{
   Tosho t(42);

   std::cout << "tosho is " << t.b << " 3+4=" << sum(3,4) << " 3 ravno li e na 3 = " << equals(3,3) <<std::endl;
   return 0;
}