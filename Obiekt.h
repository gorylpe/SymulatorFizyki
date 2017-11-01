#pragma once
#include "Wektor.h"
#include "Stale.h"
#include "Kolo.h"
#include "Wielokat.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Obiekt
{
public:
    Obiekt(Ksztalt* _ksztaltPoczatkowy);
    ~Obiekt();
    Obiekt(const Obiekt& obiekt);

    std::vector<Ksztalt*> ksztalt;

    Wektor pozycja;
    Wektor predkosc;
    Wektor sila;

    double orientacja;
    double predkoscKatowa;
    Macierz22 macierzObrotu;

    double masa;
    double odwrotnoscMasy;

    double momentBezwladnosci;
    double odwrotnoscMomentuBezwladnosci;

    void DodajKsztalt(Ksztalt* _ksztalt);
    void ObliczMase();
    void ObliczMomentBezwladnosci();
    void ObliczSrodekMasy();
    void Rysuj();
    void RysujWektorPredkosci();
    void UstawStatyczny();
    void UstawNieobrotowy();
    void KorekcjaOrientacji();
};
