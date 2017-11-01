#pragma once
#include "Wektor.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

enum TypKsztaltu
{
    TKolo,
    TWielokat
};

class Ksztalt
{
public:
    Ksztalt(Wektor _pozycja, double _gestosc, double _restytucja, double _tarcieStatyczne, double _tarcieDynamiczne,
            int _r, int _g, int _b);
    virtual ~Ksztalt();
    double gestosc;
    double restytucja;
    double tarcieStatyczne;
    double tarcieDynamiczne;
    int r,g,b;

    Wektor pozycja;

    double masa;
    double momentBezwladnosci;

    virtual TypKsztaltu ZwrocTyp() = 0;
    virtual void ObliczMase() = 0;
    virtual void ObliczMomentBezwladnosciISrodekMasy() = 0;
    virtual void Rysuj(const Wektor& pozycja, const Macierz22& macierzObrotu) = 0;
};

