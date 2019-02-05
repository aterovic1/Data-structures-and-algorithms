#ifndef NIZMAPA_H
#define NIZMAPA_H

#include "mapa.h"
const int VEL = 1000;

template <typename TipK, typename TipV>
class NizMapa : public Mapa<TipK, TipV> {
    struct Par {
        TipK key;
        TipV value;
        Par(const TipK& kljuc, const TipV& vrijednost) : key(kljuc), value(vrijednost) {}
        Par(const TipK& kljuc) : key(kljuc), value(TipV()) {}
    };
    Par** parovi;
    int kapacitet;
    int broj_el;
    void povecaj_kapacitet();
public:
    NizMapa() : Mapa<TipK, TipV>(), parovi(new Par*[VEL]), kapacitet(VEL), broj_el(0) {}
    ~NizMapa();
    NizMapa(const NizMapa<TipK, TipV>& nmapa);
    NizMapa<TipK, TipV>& operator =(const NizMapa<TipK, TipV>& nmapa);
    TipV operator [](const TipK& kljuc) const;
    TipV& operator [](const TipK& kljuc);
    int brojElemenata() const { return broj_el; }
    void obrisi();
    void obrisi(const TipK& kljuc);
};

template <typename TipK, typename TipV>
void NizMapa<TipK, TipV>::povecaj_kapacitet() {
    kapacitet *= 2;
    Par** novi = new Par*[kapacitet];
    for(int i(0); i < broj_el; i++) {
        novi[i] = new Par(parovi[i] -> key, parovi[i] -> value);
        delete parovi[i];
    }
    delete[] parovi;
    parovi = novi;
}

template <typename TipK, typename TipV>
NizMapa<TipK, TipV>::~NizMapa() {
    for(int i(0); i < broj_el; i++)
        delete parovi[i];
    delete[] parovi;
}

template <typename TipK, typename TipV>
NizMapa<TipK, TipV>::NizMapa(const NizMapa<TipK, TipV>& nmapa) {
    broj_el = nmapa.broj_el;
    kapacitet = nmapa.kapacitet;
    parovi = new Par*[kapacitet];
    for(int i(0); i < broj_el; i++)
        parovi[i] = new Par(nmapa.parovi[i] -> key, nmapa.parovi[i] -> value);
}

template <typename TipK, typename TipV>
NizMapa<TipK, TipV>& NizMapa<TipK, TipV>::operator =(const NizMapa<TipK, TipV>& nmapa) {
    if(&nmapa == this)
        return *this;
    for(int i(0); i < broj_el; i++)
        delete parovi[i];
    delete[] parovi;
    broj_el = nmapa.broj_el;
    kapacitet = nmapa.kapacitet;
    parovi = new Par*[kapacitet];
    for(int i(0); i < broj_el; i++)
        parovi[i] = new Par(nmapa.parovi[i] -> key, nmapa.parovi[i] -> value);
    return *this;
}

template <typename TipK, typename TipV>
TipV NizMapa<TipK, TipV>::operator [](const TipK& kljuc) const {
    for(int i(0); i < broj_el; i++)
        if(parovi[i] -> key == kljuc)
            return parovi[i] -> value;
    return TipV();
}

template <typename TipK, typename TipV>
TipV& NizMapa<TipK, TipV>::operator [](const TipK& kljuc) {
   for(int i(0); i < broj_el; i++)
        if(parovi[i] -> key == kljuc)
            return parovi[i] -> value;
    if(broj_el == kapacitet)
        povecaj_kapacitet();
    parovi[broj_el] = new Par(kljuc); 
    return parovi[broj_el++] -> value; 
}

template <typename TipK, typename TipV>
void NizMapa<TipK, TipV>::obrisi() {
    for(int i(0); i < broj_el; i++) 
        delete parovi[i];
    broj_el = 0;
}

template <typename TipK, typename TipV>
void NizMapa<TipK, TipV>::obrisi(const TipK& kljuc) {
    for(int i(0); i < broj_el; i++) 
        if(parovi[i] -> key == kljuc) {
            delete parovi[i];
            parovi[i] = parovi[--broj_el];
            parovi[broj_el] = nullptr;
            return;
        }
    throw "Kljuc ne postoji!";
}

#endif