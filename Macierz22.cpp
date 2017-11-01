#include "Macierz22.h"
#include <cmath>

Macierz22::Macierz22(double a, double b, double c, double d)
{
    element[0][0] = a;
    element[0][1] = b;
    element[1][0] = c;
    element[1][1] = d;
}

Macierz22::Macierz22(double kat)
{
    double c = cos(kat);
    double s = sin(kat);

    element[0][0] = c;
    element[0][1] = -s;
    element[1][0] = s;
    element[1][1] = c;
}

Macierz22::~Macierz22()
{

}

Macierz22 Macierz22::Przetransponowana() const
{
    return Macierz22(element[0][0], element[1][0], element[0][1], element[1][1]);
}

void Macierz22::Transponuj()
{
    double tmp = element[0][1];
    element[0][1] = element[1][0];
    element[1][0] = tmp;
}
