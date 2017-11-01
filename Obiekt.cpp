#include "Obiekt.h"

Obiekt::Obiekt(Ksztalt* _ksztaltPoczatkowy)
: orientacja(0)
, macierzObrotu(0)
, predkosc(0, 0)
, sila(0, 0)
, predkoscKatowa(0)
, masa(0)
, momentBezwladnosci(0)
{
    switch(_ksztaltPoczatkowy->ZwrocTyp())
    {
    case TKolo:
        ksztalt.push_back(new Kolo(*reinterpret_cast<Kolo*>(_ksztaltPoczatkowy)));
        break;
    case TWielokat:
        ksztalt.push_back(new Wielokat(*reinterpret_cast<Wielokat*>(_ksztaltPoczatkowy)));
        break;
    }
    pozycja = ksztalt[0]->pozycja;
    ksztalt[0]->pozycja = Wektor(0,0);
}

Obiekt::Obiekt(const Obiekt& obiekt)
: orientacja(obiekt.orientacja)
, macierzObrotu(obiekt.orientacja)
, predkosc(obiekt.predkosc)
, sila(obiekt.sila)
, predkoscKatowa(obiekt.predkoscKatowa)
, masa(obiekt.masa)
, momentBezwladnosci(obiekt.momentBezwladnosci)
, pozycja(obiekt.pozycja)
{
    ksztalt.reserve(obiekt.ksztalt.size());
    for(int i = 0; i < obiekt.ksztalt.size(); ++i)
    {
        switch(obiekt.ksztalt[i]->ZwrocTyp())
        {
        case TKolo:
            ksztalt.push_back(new Kolo(*reinterpret_cast<Kolo*>(obiekt.ksztalt[i])));
            break;
        case TWielokat:
            ksztalt.push_back(new Wielokat(*reinterpret_cast<Wielokat*>(obiekt.ksztalt[i])));
            break;
        }
    }
}

Obiekt::~Obiekt()
{
#ifndef DEBUG
    log("~Obiekt");
#endif
    for(int i = 0; i < ksztalt.size(); ++i)
    {
        delete ksztalt[i];
    }
}

void Obiekt::Rysuj()
{
    for(int i = 0; i < ksztalt.size(); ++i)
    {
        ksztalt[i]->Rysuj(pozycja, macierzObrotu);
    }
    if(masa)
        al_draw_filled_circle(pozycja.x, pozycja.y, 3, al_map_rgb(0, 0, 0));
}

void Obiekt::RysujWektorPredkosci()
{
    al_draw_line(pozycja.x, pozycja.y, pozycja.x + predkosc.x / 5, pozycja.y + predkosc.y / 5, al_map_rgb(128, 128, 255), 2);
}

void Obiekt::KorekcjaOrientacji()
{
    if(orientacja > M_2PI)
    {
        do
        {
            orientacja -= M_2PI;
        }while(orientacja > M_2PI);
    }
    else if(orientacja < 0)
    {
        do
        {
            orientacja += M_2PI;
        }while(orientacja < 0);
    }
}

void Obiekt::ObliczMase()
{
    for(int i = 0; i < ksztalt.size(); ++i)
    {
        ksztalt[i]->ObliczMase();
        masa += ksztalt[i]->masa;
    }
    odwrotnoscMasy = masa ? 1.0/masa : 0.0;
}

void Obiekt::ObliczMomentBezwladnosci()
{
    for(int i = 0; i < ksztalt.size(); ++i)
    {
        ksztalt[i]->ObliczMomentBezwladnosciISrodekMasy();
        double dlugosc = ksztalt[i]->pozycja.Modul();
        momentBezwladnosci += ksztalt[i]->momentBezwladnosci + ksztalt[i]->masa * dlugosc * dlugosc;//Twierdzenie Steinera
    }
    odwrotnoscMomentuBezwladnosci = momentBezwladnosci ? 1.0/momentBezwladnosci : 0.0;
    ObliczSrodekMasy();
}

void Obiekt::ObliczSrodekMasy()
{
    Wektor licznik = Wektor(0,0);
    double mianownik = 0;
    for(int i = 0; i < ksztalt.size(); ++i)
    {
        licznik += ksztalt[i]->masa * ksztalt[i]->pozycja;
        mianownik += ksztalt[i]->masa;
    }
    Wektor wektorPrzesuniecia = licznik * (1.0/mianownik);
    pozycja += wektorPrzesuniecia;
    for(int i = 0; i < ksztalt.size(); ++i)
    {
        ksztalt[i]->pozycja -= wektorPrzesuniecia;
    }
}

void Obiekt::DodajKsztalt(Ksztalt* _ksztalt)
{
    switch(_ksztalt->ZwrocTyp())
    {
    case TKolo:
        {
            Kolo* kolo = new Kolo(*reinterpret_cast<Kolo*>(_ksztalt));
            kolo->pozycja -= pozycja; // Pozycja wzgledem 1. ksztaltu
            ksztalt.push_back(kolo);
        }
        break;
    }
}
