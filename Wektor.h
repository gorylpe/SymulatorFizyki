#pragma once
#include <cmath>
#include "Macierz22.h"

class Wektor
{
public:
    double x;
    double y;
    Wektor();
    Wektor(double _x, double _y);
    void Ustaw(double _x, double _y);
    double KwadratModulu();
    double Modul();
    Wektor Unormowany();
    void Normalizuj();
    Wektor Obrocony(const Macierz22& m);
    void Obroc(const Macierz22& m);
    ~Wektor();

    Wektor operator!() const
    {
        return Wektor(- this->x, - this->y);
    }
    Wektor operator-() const
    {
        return Wektor(- this->x, - this->y);
    }
    bool operator==(const Wektor& u) const
    {
        if(this->x == u.x && this->y == u.y)
            return true;
        return false;
    }
    Wektor operator-(const Wektor& u) const
    {
        return Wektor(this->x - u.x, this->y - u.y);
    }
    Wektor operator-=(const Wektor& u)
    {
        this->x -= u.x;
        this->y -= u.y;
        return *this;
    }
    Wektor operator+(const Wektor& u) const
    {
        return Wektor(this->x + u.x, this->y + u.y);
    }
    Wektor operator+=(const Wektor& u)
    {
        this->x += u.x;
        this->y += u.y;
        return *this;
    }
    Wektor operator*(const double& k) const
    {
        return Wektor(this->x * k, this->y * k);
    }
    Wektor operator*=(const double& k)
    {
        this->x *= k;
        this->y *= k;
        return *this;
    }
    Wektor operator/(const double& k) const
    {
        return Wektor(this->x / k, this->y / k);
    }
    Wektor operator/=(const double& k)
    {
        this->x /= k;
        this->y /= k;
        return *this;
    }
};

Wektor operator*(const double& k, const Wektor& u);

double IloczynSkalarny(const Wektor& u, const Wektor& v);

double IloczynWektorowy(const Wektor& u, const Wektor& v);

Wektor IloczynWektorowy(double a, const Wektor& u);

Wektor IloczynWektorowy(const Wektor& u, double a);



