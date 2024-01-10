#include <iostream>
#include "randomTests.h"

int main(int argc, char *argv[])
{
   Tosho t(42);

   std::cout << "tosho is " << t.b << " sum " << sum(3,4) << " 3==3 = " << equals(3,3) << std::endl;
   return 0;
}