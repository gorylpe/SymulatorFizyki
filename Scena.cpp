#include "Scena.h"
#include <iostream>

Scena::Scena(double _dt, double _liczbaWykonywanychImpulsowNaRaz)
: dt(_dt), liczbaWykonywanychImpulsowNaRaz(_liczbaWykonywanychImpulsowNaRaz)
{

}

Scena::~Scena()
{

}


void Scena::CalkujSily(Obiekt* A, double dt)
{
    if(A->odwrotnoscMasy == 0)
    {
        return;
    }
    A->predkosc += (A->sila * A->odwrotnoscMasy + stalePrzyspieszenie) * dt;
}

void Scena::CalkujPredkosci(Obiekt* A, double dt)
{
    if(A->odwrotnoscMasy == 0)
        return;

    A->pozycja += A->predkosc * dt;
    A->orientacja += A->predkoscKatowa * dt;
    A->macierzObrotu = Macierz22(A->orientacja);
}

void Scena::Krok()
{
    for(int i = 0; i < obiekty.size(); ++i)
    {
        obiekty[i]->KorekcjaOrientacji();
    }

    //GENEROWANIE LISTY WSZYSTKICH KOLIZJI
    kolizje.clear();
    for(int i = 0; i < obiekty.size(); ++i)
    {
        Obiekt* A = obiekty[i];
        for(int j = i + 1; j < obiekty.size(); ++j)
        {
            Obiekt* B = obiekty[j];
            if(A->odwrotnoscMasy == 0 && B->odwrotnoscMasy == 0)
                continue;
            Kolizja* kolizja = new Kolizja(A, B);
            kolizja->SprawdzKolizje();
            if(kolizja->liczbaKontaktow)
            {
                kolizje.push_back(kolizja);
            }
        }
    }

    for(int i = 0; i < kolizje.size(); ++i)
    {
        for(int j = 0; j < liczbaWykonywanychImpulsowNaRaz; ++j)
            kolizje[i]->RozwiazKolizje();
    }

    for(int i = 0; i < obiekty.size(); ++i)
    {
        CalkujSily(obiekty[i], dt);
    }

    for(int i = 0; i < obiekty.size(); ++i)
    {
        CalkujPredkosci(obiekty[i], dt);
    }

    std::vector<int> obiektyDoUsuniecia;

    for(int i = 0; i < obiekty.size(); ++i)
    {
        if(obiekty[i]->pozycja.x > 1044 || obiekty[i]->pozycja.x < -20 || obiekty[i]->pozycja.y < -20 || obiekty[i]->pozycja.y > 620)
        {
            obiektyDoUsuniecia.push_back(i);
        }
    }

    for(int i = obiektyDoUsuniecia.size() - 1; i >= 0; --i){
        delete obiekty[obiektyDoUsuniecia[i]];
        obiekty.erase(obiekty.begin() + obiektyDoUsuniecia[i]);
    }

    for(int i = 0; i < obiekty.size(); ++i)
    {
        obiekty[i]->sila.Ustaw(0, 0);
    }

    for(int i = 0; i < kolizje.size(); ++i)
    {
        kolizje[i]->KorekcjaPozycji();
    }

    for(int i = 0; i < kolizje.size(); ++i){
        delete kolizje[i];
    }
    kolizje.clear();
}

void Scena::Rysuj()
{
    for(int i = 0; i < obiekty.size(); ++i)
    {
        obiekty[i]->Rysuj();
    }
    for(int i = 0; i < obiekty.size(); ++i)
    {
        obiekty[i]->RysujWektorPredkosci();
    }
    for(int i = 0; i < kolizje.size(); ++i)
    {
        for(int j = 0; j < kolizje[i]->liczbaKolizji; ++j)
        {
            for(int k = 0; k < kolizje[i]->liczbaKontaktow[j]; ++k)
            {
                al_draw_filled_rectangle(kolizje[i]->miejsceKontaktu[j][k].x - 2, kolizje[i]->miejsceKontaktu[j][k].y - 2,
                    kolizje[i]->miejsceKontaktu[j][k].x + 2, kolizje[i]->miejsceKontaktu[j][k].y + 2, al_map_rgb(255,0,0));
            }
        }
    }
}

Obiekt* Scena::DodajObiekt(Obiekt* _obiekt, TypObiektu typ)
{
    Obiekt* obiekt;
    switch(typ)
    {
    case TNormalny:
        {
            obiekt = new Obiekt(*_obiekt);
            obiekt->ObliczMase();
            obiekt->ObliczMomentBezwladnosci();
        }
        break;
    case TNieobrotowy:
        {
            obiekt = new Obiekt(*_obiekt);
            obiekt->ObliczMase();
            obiekt->momentBezwladnosci = 0;
            obiekt->odwrotnoscMomentuBezwladnosci = 0;
        }
        break;
    case TStatyczny:
        {
            obiekt = new Obiekt(*_obiekt);
            obiekt->momentBezwladnosci = 0;
            obiekt->odwrotnoscMomentuBezwladnosci = 0;
            obiekt->masa = 0;
            obiekt->odwrotnoscMasy = 0;
        }
        break;
    }
    obiekty.push_back(obiekt);
    return obiekt;
}
