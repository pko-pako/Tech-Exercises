#pragma once

class Tosho {
public:
    int b;
    Tosho(int a);
};

int sum(int a, int b);
bool equals(int a, int b);

extern "C" __declspec(dllexport) int __cdecl multiply(int a, int b);