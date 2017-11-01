#pragma once
#include "Wektor.h"
#include <cstdlib>
#include <iostream>
#include <cstdlib>
//#define DEBUG

#define M_2PI 6.28318530717958647692
#define M_PI 3.14159265358979323846

const Wektor stalePrzyspieszenie(0, 200); //PRZYSPIESZENIE GRAWITACYJNE
const double dt = 0.01;

inline int Losuj(int l1, int l2)
{
    return rand()%(l2 - l1 + 1) + l1;
}
inline double Przytnij(double min, double max, double a)
{
    if(a > max) return max;
    if(a < min) return min;
    return a;
}
inline void log(std::string str){
    std::cout << str << std::endl;
}
