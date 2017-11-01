#pragma once

class Macierz22
{
public:
    double element[2][2];
    Macierz22(double a, double b, double c, double d);
    Macierz22(double kat);
    ~Macierz22();
    Macierz22 Przetransponowana() const;
    void Transponuj();
};
