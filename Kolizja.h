#pragma once
#include "Kolo.h"
#include "Obiekt.h"
#include "Stale.h"
#include <cmath>
#include <algorithm>


class Kolizja
{
public:
    Obiekt* A;
    Obiekt* B;

    int liczbaKolizji;
    double* penetracja;
    Wektor* normalnaZderzenia;
    int* liczbaKontaktow;
    Wektor** miejsceKontaktu;
    double* restytucja;
    double* tarcieStatyczne;
    double* tarcieDynamiczne;

    Kolizja(Obiekt* a, Obiekt* b);
    virtual ~Kolizja();

    void SprawdzKolizje();
    void SprawdzKolizjeKoloZKolem(Ksztalt* _a, Ksztalt* _b, int numerKolizji);
    void RozwiazKolizje();
    void RozwiazPojedynczaKolizje(int numerKolizji);
    void KorekcjaPozycji();
    void KorekcjaPojedynczaPozycji(int numerKolizji, int calkowitaLiczbaKontaktow);
};
