#include "Kolizja.h"

Kolizja::Kolizja(Obiekt* a, Obiekt* b)
 : A(a)
 , B(b)
 {
    liczbaKolizji = A->ksztalt.size() * B->ksztalt.size();
    penetracja = new double[liczbaKolizji];
    normalnaZderzenia = new Wektor[liczbaKolizji];
    liczbaKontaktow = new int[liczbaKolizji];
    miejsceKontaktu = new Wektor*[liczbaKolizji];
    for(int i = 0; i < liczbaKolizji; ++i)
    {
        miejsceKontaktu[i] = new Wektor[2];
    }
    restytucja = new double[liczbaKolizji];
    tarcieStatyczne = new double[liczbaKolizji];
    tarcieDynamiczne = new double[liczbaKolizji];
 }

Kolizja::~Kolizja()
{
#ifdef DEBUG
    log("~Kolizja");
#endif
    delete[] penetracja;
    delete[] normalnaZderzenia;
    for(int i = 0; i < liczbaKolizji; ++i){
        delete[] miejsceKontaktu[i];
    }
    delete[] miejsceKontaktu;
    delete[] restytucja;
    delete[] tarcieDynamiczne;
    delete[] tarcieStatyczne;
}

void Kolizja::SprawdzKolizje()
{
    Ksztalt* a;
    Ksztalt* b;

    int numerKolizji = 0;

    for(int i = 0; i < A->ksztalt.size(); ++i)
    {
        a = A->ksztalt[i];
        for(int j = 0; j < B->ksztalt.size(); ++j)
        {
            b = B->ksztalt[j];

            restytucja[numerKolizji] = std::min(A->ksztalt[i]->restytucja, B->ksztalt[j]->restytucja);
            tarcieStatyczne[numerKolizji] = sqrt(pow(A->ksztalt[i]->tarcieStatyczne,2) + pow(B->ksztalt[j]->tarcieStatyczne,2));
            tarcieDynamiczne[numerKolizji] = sqrt(pow(A->ksztalt[i]->tarcieDynamiczne,2) + pow(B->ksztalt[j]->tarcieDynamiczne,2));

            if(a->ZwrocTyp() == TKolo)
            {
                if(b->ZwrocTyp() == TKolo)
                {
                    SprawdzKolizjeKoloZKolem(a, b, numerKolizji);
                }
                else if(b->ZwrocTyp() == TWielokat)
                {

                }
            }
            else if(a->ZwrocTyp() == TWielokat)
            {
                if(b->ZwrocTyp() == TKolo)
                {

                }
                else if(b->ZwrocTyp() == TWielokat)
                {

                }
            }
            ++numerKolizji;
        }
    }
}

void Kolizja::SprawdzKolizjeKoloZKolem(Ksztalt* _a, Ksztalt* _b, int numerKolizji)
{
    Kolo *a = reinterpret_cast<Kolo*>(_a);
    Kolo *b = reinterpret_cast<Kolo*>(_b);

    Wektor pozycjaA = A->pozycja + a->pozycja.Obrocony(A->macierzObrotu);
    Wektor pozycjaB = B->pozycja + b->pozycja.Obrocony(B->macierzObrotu);

    Wektor odAdoB = pozycjaB - pozycjaA;
    double suma_promieni = b->promien + a->promien;
    double odleglosc = odAdoB.Modul();

    if(odleglosc >= suma_promieni)
    {
        liczbaKontaktow[numerKolizji] = 0;
    }
    else
    {
        liczbaKontaktow[numerKolizji] = 1;

        if(odleglosc == 0.0)
        {
            penetracja[numerKolizji] = a->promien;
            normalnaZderzenia[numerKolizji] = Wektor(1, 0);
            miejsceKontaktu[numerKolizji][0] = pozycjaA;
        }
        else
        {
            penetracja[numerKolizji] = suma_promieni - odleglosc;
            normalnaZderzenia[numerKolizji] = odAdoB / odleglosc;
            miejsceKontaktu[numerKolizji][0] = a->promien * normalnaZderzenia[numerKolizji] + pozycjaA;
        }
    }
}

void Kolizja::RozwiazKolizje()
{
    for(int i = 0; i < liczbaKolizji; ++i)
    {
        if(liczbaKontaktow[i])
            RozwiazPojedynczaKolizje(i);
    }
}

void Kolizja::RozwiazPojedynczaKolizje(int numerKolizji)
{
    for(int i = 0; i < liczbaKontaktow[numerKolizji]; ++i)
    {
        Wektor promienB = miejsceKontaktu[numerKolizji][i] - B->pozycja;
        Wektor promienA = miejsceKontaktu[numerKolizji][i] - A->pozycja;

        Wektor predkoscWzgledna = B->predkosc + IloczynWektorowy(B->predkoscKatowa, promienB)- A->predkosc - IloczynWektorowy(A->predkoscKatowa, promienA);

        double predkoscWzdluzNormalnej = IloczynSkalarny(predkoscWzgledna, normalnaZderzenia[numerKolizji]);
        if(predkoscWzdluzNormalnej > 0)
        {
            return;
        }
        double IlWekA = IloczynWektorowy(promienA, normalnaZderzenia[numerKolizji]);
        double IlWekB = IloczynWektorowy(promienB, normalnaZderzenia[numerKolizji]);

        double sumaOdwroconychMasMomentowBezwladnosci = A->odwrotnoscMasy + B->odwrotnoscMasy +
                                                         pow(IlWekA, 2) * A->odwrotnoscMomentuBezwladnosci +
                                                         pow(IlWekB, 2) * B->odwrotnoscMomentuBezwladnosci;

        double j = 1 + restytucja[numerKolizji]; //MODU£ POPÊDU SI£Y LEZACEJ NA NORMALNEJ
        j *= predkoscWzdluzNormalnej;
        j /= sumaOdwroconychMasMomentowBezwladnosci;

        Wektor poped = j * normalnaZderzenia[numerKolizji]; //POPÊD SI£Y (IMPULS)
        A->predkosc += A->odwrotnoscMasy * poped;
        B->predkosc -= B->odwrotnoscMasy * poped;
        A->predkoscKatowa += IloczynWektorowy(promienA, poped) * A->odwrotnoscMomentuBezwladnosci;
        B->predkoscKatowa -= IloczynWektorowy(promienB, poped) * B->odwrotnoscMomentuBezwladnosci;

        //TARCIE

        //predkoscWzgledna = B->predkosc + IloczynWektorowy(B->predkoscKatowa, promienB)- A->predkosc - IloczynWektorowy(A->predkoscKatowa, promienA);

        Wektor kierunekTarcia = predkoscWzgledna - predkoscWzdluzNormalnej * normalnaZderzenia[numerKolizji]; //WEKTOR PROSTEJ NA KTÓREJ LE¯Y WEKTOR TARCIA

        kierunekTarcia.Normalizuj();
        kierunekTarcia = -kierunekTarcia; //BO TARCIE DZIA£A W PRZECIWN¥ STRONÊ CO WEKTOR PRÊDKOŒCI

        double jt = IloczynSkalarny(predkoscWzgledna, kierunekTarcia); //POPED SI£Y TARCIA KTÓRY WYHAMUJE CIA£O, V' = 0;
        jt /= sumaOdwroconychMasMomentowBezwladnosci;

        if(fabs(jt) < fabs(j * tarcieStatyczne[numerKolizji])) //JEŒLI POPÊD TARCIA STATYCZNEGO WYHAMUJE CIA£O TO NIECH TO ZROBI
        {
            poped = jt * kierunekTarcia; //TO WYHAMUJ TO CIA£O DO 0;
        }
        else //W INNYM WYPADKU ZMNIEJSZ PRÊDKOŒÆ, BO NIE DA RADY WYHAMOWAÆ DO ZERA
        {
            poped = j * kierunekTarcia * tarcieDynamiczne[numerKolizji];
        }
        A->predkosc += A->odwrotnoscMasy * poped;
        B->predkosc -= B->odwrotnoscMasy * poped;
        A->predkoscKatowa += IloczynWektorowy(promienA, poped) * A->odwrotnoscMomentuBezwladnosci;
        B->predkoscKatowa -= IloczynWektorowy(promienB, poped) * B->odwrotnoscMomentuBezwladnosci;
        #ifdef DEBUG
        std::cout << "Kolizja:" << numerKolizji << std::endl;
        std::cout << "miejsceKontaktu:" << miejsceKontaktu[numerKolizji][0].x << "," << miejsceKontaktu[numerKolizji][0].y << std::endl;
        std::cout << "deltaPozycjaB:" << B->pozycja.x << "," << B->pozycja.y << std::endl;
        std::cout << "promienB:" << promienB.x << "," << promienB.y << std::endl;
        std::cout << "normalnaZderzenia:" << normalnaZderzenia[numerKolizji].x << "," << normalnaZderzenia[numerKolizji].y << std::endl;
        std::cout << std::endl;
        #endif // DEBUG
    }
}

void Kolizja::KorekcjaPozycji()
{
    int calkowitaLiczbaKontaktow = 0;
    for(int i = 0; i < liczbaKolizji; ++i)
    {
        calkowitaLiczbaKontaktow += liczbaKontaktow[i];
    }
    for(int i = 0; i < liczbaKolizji; ++i)
    {
        if(liczbaKontaktow[i]) //Jesli jest kolizja
            KorekcjaPojedynczaPozycji(i, calkowitaLiczbaKontaktow);
    }
}

void Kolizja::KorekcjaPojedynczaPozycji(int numerKolizji, int calkowitaLiczbaKontaktow)
{
    double minimalnaPenetracja = 0.1;
    double procent = 0.6;
    Wektor korekcja = (penetracja[numerKolizji] > minimalnaPenetracja ? penetracja[numerKolizji] : 0.0) * normalnaZderzenia[numerKolizji] * procent / calkowitaLiczbaKontaktow;
    double sumaOdwrotnosciMas = A->odwrotnoscMasy + B->odwrotnoscMasy;
    A->pozycja -= (A->odwrotnoscMasy / sumaOdwrotnosciMas) * korekcja;
    B->pozycja += (B->odwrotnoscMasy / sumaOdwrotnosciMas) * korekcja;
}
