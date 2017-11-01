#include "Ksztalt.h"

Ksztalt::Ksztalt(Wektor _pozycja, double _gestosc, double _restytucja, double _tarcieStatyczne, double _tarcieDynamiczne,
                 int _r, int _g, int _b)
: restytucja(_restytucja)
, gestosc(_gestosc)
, tarcieDynamiczne(_tarcieDynamiczne)
, tarcieStatyczne(_tarcieStatyczne)
, pozycja(_pozycja)
, r(_r)
, g(_g)
, b(_b)
{

}

Ksztalt::~Ksztalt()
{
#ifdef DEBUG
    log("~Ksztalt");
#endif
}
