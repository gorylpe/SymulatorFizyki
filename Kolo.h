#pragma once
#include "Ksztalt.h"
#include "Stale.h"

class Kolo : public Ksztalt
{
public:
    Kolo(Wektor _pozycja, double _gestosc, double _restytucja, double _tarcieStatyczne, double _tarcieDynamiczne,
                 int _r, int _g, int _b, double _promien);
    ~Kolo();

    double promien;

    TypKsztaltu ZwrocTyp();
    void ObliczMase();
    void ObliczMomentBezwladnosciISrodekMasy();
    void Rysuj(const Wektor& pozycja, const Macierz22& macierzObrotu);
};
