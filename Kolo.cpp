#include <math.h>
#include "Kolo.h"

Kolo::Kolo(Wektor _pozycja, double _gestosc, double _restytucja, double _tarcieStatyczne, double _tarcieDynamiczne,
                 int _r, int _g, int _b, double _promien)
: Ksztalt(_pozycja, _gestosc, _restytucja, _tarcieStatyczne, _tarcieDynamiczne, _r, _g, _b)
, promien(_promien)
{

}

Kolo::~Kolo()
{
#ifdef DEBUG
    log("~Kolo");
#endif
}

void Kolo::ObliczMase()
{
    masa = M_PI * promien * promien * gestosc / 1000000;
}

void Kolo::ObliczMomentBezwladnosciISrodekMasy()
{
    momentBezwladnosci = promien * promien * masa / 2;
}

TypKsztaltu Kolo::ZwrocTyp()
{
    return TKolo;
}

void Kolo::Rysuj(const Wektor& pozycja, const Macierz22& macierzObrotu)
{
    if(this->pozycja == Wektor(0,0))
    {
        al_draw_filled_circle(pozycja.x, pozycja.y, promien, al_map_rgb(r, g, b));
    }
    else
    {
        Wektor tmp = this->pozycja.Obrocony(macierzObrotu);
        Wektor nowaPozycja = pozycja + tmp;
        al_draw_filled_circle(nowaPozycja.x, nowaPozycja.y, promien, al_map_rgb(r, g, b));
    }
}
