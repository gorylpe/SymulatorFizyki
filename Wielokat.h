#pragma once
#include "Ksztalt.h"
#include "Stale.h"
#include <vector>


class Wielokat : public Ksztalt
{
public:
    Wielokat(Wektor _pozycja, double _gestosc, double _restytucja, double _tarcieStatyczne, double _tarcieDynamiczne,
                 int _r, int _g, int _b);
    ~Wielokat();

    std::vector<Wektor> wierzcholek;
    std::vector<Wektor> normalna;

    TypKsztaltu ZwrocTyp();
    void ObliczMase();
    void ObliczMomentBezwladnosciISrodekMasy();
    void Rysuj(const Wektor& pozycja, const Macierz22& macierzObrotu);
    void DodajWierzcholek(Wektor pozycjaWierzcholka);

};
