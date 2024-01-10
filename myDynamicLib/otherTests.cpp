#include "randomTests.h"
 
extern "C" __declspec(dllexport) int __cdecl multiply(int a, int b){
    return a * b;
}