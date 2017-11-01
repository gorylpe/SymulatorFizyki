#pragma once
#include <vector>
#include "Kolizja.h"
#include "Obiekt.h"
#include "Kolo.h"

enum TypObiektu
{
    TNormalny,
    TNieobrotowy,
    TStatyczny
};

class Scena
{
public:
    Scena(double _dt, double _liczbaWykonywanychImpulsowNaRaz);
    virtual ~Scena();

    void Krok();
    void Rysuj();

    void CalkujSily(Obiekt* A, double dt);
    void CalkujPredkosci(Obiekt* A, double dt);

    Obiekt* DodajObiekt(Obiekt* _obiekt, TypObiektu typ);

    double dt;
    double liczbaWykonywanychImpulsowNaRaz; //Do zderzeń z wieloma ciałami na raz. Np. gdy piłeczka o restytucji < 1 zostanie ściśnięta z góry i z dołu to po kilku (-nastu, -set) impulsach prędkość się wyzeruje

    std::vector<Obiekt*> obiekty;
    std::vector<Kolizja*> kolizje;
};
