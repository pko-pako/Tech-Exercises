#include <iostream>
#include "actionsStatic.h"
#include "actionsDynamic.h"

int main(int argc, char *argv[])
{
   Tosho t(42);

   std::cout << "tosho is " << t.b << " 3+4=" << sum(3,4) << " 3 ravno li e na 3 = " << equals(3,3) <<std::endl;
   std::cout << "7 po 4 e" << multiply(7,4) << std::endl;
   return 0;
}