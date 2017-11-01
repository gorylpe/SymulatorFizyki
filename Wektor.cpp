#include "Wektor.h"

Wektor::Wektor(double _x, double _y)
: x(_x)
, y(_y)
{

}
Wektor::Wektor()
{

}

Wektor::~Wektor()
{
}

void Wektor::Ustaw(double _x, double _y)
{
    x = _x;
    y = _y;
}

double Wektor::KwadratModulu()
{
    return x*x + y*y;
}

double Wektor::Modul()
{
    return std::sqrt(x*x + y*y);
}

Wektor Wektor::Unormowany()
{
    double modul = this->Modul();
    if(modul != 0)
    {
        return Wektor(this->x / modul, this->y / modul);
    }
    return *this;
}

void Wektor::Normalizuj()
{
    double modul = Modul();
    if(modul != 0)
    {
        this->x /= modul;
        this->y /= modul;
    }
}

Wektor Wektor::Obrocony(const Macierz22& m)
{
    return Wektor(this->x * m.element[0][0] + this->y * m.element[0][1], this->x * m.element[1][0] + this->y * m.element[1][1]);
}

void Wektor::Obroc(const Macierz22& m)
{
    double x = this->x * m.element[0][0] + this->y * m.element[0][1];
    double y = this->x * m.element[1][0] + this->y * m.element[1][1];
    this->x = x;
    this->y = y;
}

Wektor operator*(const double& k, const Wektor& u)
{
    return Wektor(u.x * k, u.y * k);
}

double IloczynSkalarny(const Wektor& u, const Wektor& v)
{
    return u.x * v.x + u.y * v.y;
}

double IloczynWektorowy(const Wektor& u, const Wektor& v)
{
    return u.x * v.y - u.y * v.x;
}

Wektor IloczynWektorowy(double a, const Wektor& u)
{
    return Wektor(-a * u.y, a * u.x);
}

Wektor IloczynWektorowy(const Wektor& u, double a)
{
    return Wektor(a * u.y, -a * u.x);
}

double KwadratOdleglosci(const Wektor& u, const Wektor& v)
{
    return pow(v.x - u.x, 2) + pow(v.y - v.x, 2);
}

double Odleglosc(const Wektor& u, const Wektor& v)
{
    return sqrt(KwadratOdleglosci(u,v));
}

