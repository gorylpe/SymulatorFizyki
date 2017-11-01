#include "Wielokat.h"

Wielokat::Wielokat(Wektor _pozycja, double _gestosc, double _restytucja, double _tarcieStatyczne, double _tarcieDynamiczne,
                 int _r, int _g, int _b)
: Ksztalt(_pozycja, _gestosc, _restytucja, _tarcieStatyczne, _tarcieDynamiczne, _r, _g, _b)
{
    wierzcholek.push_back(_pozycja - pozycja);
}

Wielokat::~Wielokat()
{
#ifdef DEBUG
    log("~Wielokat");
#endif
}

void Wielokat::ObliczMase()
{
    double pole = 0;
    normalna.reserve(wierzcholek.size());
    for(int i = 0; i < wierzcholek.size(); ++i)
    {
        Wektor w1 = wierzcholek[i];
        Wektor w2 = wierzcholek[(i+1)%wierzcholek.size()];

        Wektor styczna = (w2 - w1).Unormowany();
        normalna.push_back(Wektor(-styczna.y, styczna.x));

        pole += IloczynWektorowy(w2 - w1, -w1) / 2; //Pole rownolegloboku/2 = pole trojkata
    }
    masa = pole * gestosc / 1000000;
}

void Wielokat::ObliczMomentBezwladnosciISrodekMasy()
{
    Wektor centroidTrojkata[wierzcholek.size()];
    double momentBezwladnosciTrojkata[wierzcholek.size()];
    double masaTrojkata[wierzcholek.size()];
    momentBezwladnosci = 0;
    for(int i = 0; i < wierzcholek.size(); ++i)
    {
        Wektor w1 = wierzcholek[i];
        Wektor w2 = wierzcholek[(i+1)%wierzcholek.size()];

        Wektor styczna = Wektor(normalna[i].y, -normalna[i].x);

        // http://lab.polygonal.de/?p=57

        double h = IloczynSkalarny(w1, normalna[i]);
        double a = IloczynSkalarny(w2, styczna);
        double b = (w2 - w1).Modul();

        centroidTrojkata[i] = Wektor((w1.x + w2.x)/3, (w1.y + w2.y)/3); //pomijam w3 czyli centroid bo ma wsp 0,0

        double pole = b * h / 2;
        momentBezwladnosciTrojkata[i] = pole * (b*b - b*a + a*a + h*h) / 18;
        masaTrojkata[i] = pole * gestosc / 1000000;
    }
    Wektor licznik = Wektor(0,0);
    double mianownik = 0;
    for(int i = 0; i < wierzcholek.size(); ++i)
    {
        licznik += masaTrojkata[i] * centroidTrojkata[i];
        mianownik += masaTrojkata[i];
    }
    Wektor wektorPrzesuniecia = licznik * (1.0/mianownik);
    pozycja += wektorPrzesuniecia;
    for(int i = 0; i < wierzcholek.size(); ++i)
    {
        wierzcholek[i] -= wektorPrzesuniecia;
    }
}

TypKsztaltu Wielokat::ZwrocTyp()
{
    return TWielokat;
}

void Wielokat::DodajWierzcholek(Wektor pozycjaWierzcholka)
{
    wierzcholek.push_back(pozycjaWierzcholka - pozycja);
}

void Wielokat::Rysuj(const Wektor& pozycja, const Macierz22& macierzObrotu)
{
    std::vector<Wektor> wierzcholekNowy;
    wierzcholekNowy.reserve(wierzcholek.size());

    for(int i = 0; i < wierzcholek.size(); ++i)
    {
        wierzcholekNowy.push_back((this->pozycja + wierzcholek[i]).Obrocony(macierzObrotu));
    }
    for(int i = 0; i < wierzcholekNowy.size(); ++i)
    {
        Wektor w1 = wierzcholekNowy[i] + pozycja;
        Wektor w2 = wierzcholekNowy[(i+1)%wierzcholekNowy.size()] + pozycja;
        al_draw_line(w1.x, w1.y, w2.x, w2.y, al_map_rgb(0, 255, 0), 2);
    }
}
