#ifndef HASHMAPA_H
#define HASHMAPA_H

#include "mapa.h"
const int VEL = 1000;

template <typename TipK, typename TipV>
class HashMapa : public Mapa<TipK, TipV> {
    struct Par {
        TipK key;
        TipV value;
        bool obrisan;
        Par(const TipK& kljuc, const TipV& vrijednost, bool obr) : key(kljuc), value(vrijednost), obrisan(obr) {}
        Par(const TipK& kljuc, bool obr) : key(kljuc), value(TipV()), obrisan(obr) {}
    };
    Par** parovi;
    int kapacitet;
    int broj_el;
    unsigned int (*h)(TipK, unsigned int);
    void povecaj_kapacitet();
public:
    HashMapa();
    ~HashMapa();
    HashMapa(const HashMapa<TipK, TipV>& hmapa);
    HashMapa<TipK, TipV>& operator =(const HashMapa<TipK, TipV>& hmapa);
    TipV operator [](const TipK& kljuc) const;
    TipV& operator [](const TipK& kljuc);
    int brojElemenata() const { return broj_el; }
    void obrisi();
    void obrisi(const TipK& kljuc);
    void definisiHashFunkciju(unsigned int (*f)(TipK, unsigned int)) { h = f; }
};

template <typename TipK, typename TipV>
void HashMapa<TipK, TipV>::povecaj_kapacitet() {
    kapacitet *= 2;
    Par** novi = new Par*[kapacitet];
    for(int i(0); i < kapacitet; i++)
        novi[i] = nullptr;
    for(int i(0); i < kapacitet / 2; i++) {
        if(parovi[i] != nullptr && !parovi[i] -> obrisan) {
            int indeks;
            unsigned int hash = h(parovi[i] -> key, kapacitet);
            for(int j(0); j < kapacitet; j++) {
                indeks = (hash + j) % kapacitet;
                if(novi[indeks] == nullptr) {
                    novi[indeks] = new Par(parovi[i] -> key, parovi[i] -> value, parovi[i] -> obrisan);
                    break;
                }
            }
            delete parovi[i];
        }
    }
    delete[] parovi;
    parovi = novi;
}

template <typename TipK, typename TipV>
HashMapa<TipK, TipV>::HashMapa() : Mapa<TipK, TipV>() {
    parovi = new Par*[VEL];
    kapacitet = VEL;
    broj_el = 0;
    h = nullptr;
    for(int i(0); i < kapacitet; i++)
        parovi[i] = nullptr;
}

template <typename TipK, typename TipV>
HashMapa<TipK, TipV>::~HashMapa() {
    for(int i(0); i < kapacitet; i++) {
        if(parovi[i] != nullptr)
            delete parovi[i];
    }
    delete[] parovi;
}

template <typename TipK, typename TipV>
HashMapa<TipK, TipV>::HashMapa(const HashMapa<TipK, TipV>& hmapa) {
    broj_el = hmapa.broj_el;
    kapacitet = hmapa.kapacitet;
    h = hmapa.h;
    parovi = new Par*[kapacitet];
    for(int i(0); i < kapacitet; i++) {
        if(hmapa.parovi[i] != nullptr)
            parovi[i] = new Par(hmapa.parovi[i] -> key, hmapa.parovi[i] -> value, hmapa.parovi[i] -> obrisan);
        else
            parovi[i] = nullptr;
    }
}

template <typename TipK, typename TipV>
HashMapa<TipK, TipV>& HashMapa<TipK, TipV>::operator =(const HashMapa<TipK, TipV>& hmapa) {
    if(&hmapa == this)
        return *this;
    for(int i(0); i < kapacitet; i++) {
        if(parovi[i] != nullptr)
            delete parovi[i];
    }
    delete[] parovi;
    broj_el = hmapa.broj_el;
    kapacitet = hmapa.kapacitet;
    h = hmapa.h;
    parovi = new Par*[kapacitet];
    for(int i(0); i < kapacitet; i++) {
        if(hmapa.parovi[i] != nullptr)
            parovi[i] = new Par(hmapa.parovi[i] -> key, hmapa.parovi[i] -> value, hmapa.parovi[i] -> obrisan);
        else
            parovi[i] = nullptr;
    }
    return *this;
}

template <typename TipK, typename TipV>
TipV HashMapa<TipK, TipV>::operator [](const TipK& kljuc) const {
    if(!h)
        throw "GRESKA!";
    unsigned int hash = h(kljuc, kapacitet);
    int indeks;
    for(int i(0); i < kapacitet; i++) {
        indeks = (hash + i) % kapacitet;
        if(parovi[indeks] != nullptr) {
            if(parovi[indeks] -> key == kljuc && !parovi[indeks] -> obrisan)
                return parovi[indeks] -> value;
        }
        else
            return TipV();
    }
    return TipV();    
}

template <typename TipK, typename TipV>
TipV& HashMapa<TipK, TipV>::operator [](const TipK& kljuc) {
    if(!h)
        throw "GRESKA!";
    if(broj_el + kapacitet / 10 >= kapacitet)
        povecaj_kapacitet();
    unsigned int hash = h(kljuc, kapacitet);
    int indeks, indeksUmetanja = -1;
    for(int i(0); i < kapacitet; i++) {
        indeks = (hash + i) % kapacitet;
        if(parovi[indeks] != nullptr) {
            if(parovi[indeks] -> key == kljuc && !parovi[indeks] -> obrisan)
                return parovi[indeks] -> value;
            if(parovi[indeks] -> obrisan && indeksUmetanja == -1)
                indeksUmetanja = indeks;
        }
        else {
            if(indeksUmetanja == -1) {
                parovi[indeks] = new Par(kljuc, false);
                broj_el++;
                return parovi[indeks] -> value;
            }
            else {
                delete parovi[indeksUmetanja];
                parovi[indeksUmetanja] = new Par(kljuc, false);
                broj_el++;
                return parovi[indeksUmetanja] -> value;
            }
        }
    }
}

template <typename TipK, typename TipV>
void HashMapa<TipK, TipV>::obrisi() {
    for(int i(0); i < kapacitet; i++) {
        if(parovi[i] != nullptr) {
            delete parovi[i];
            parovi[i] = nullptr;
        }
    }
    broj_el = 0;
}

template <typename TipK, typename TipV>
void HashMapa<TipK, TipV>::obrisi(const TipK& kljuc) {
    unsigned int hash = h(kljuc, kapacitet);
    unsigned int indeks;
    for(int i(0); i < kapacitet; i++) {
        indeks = (hash + i) % kapacitet;
        if(parovi[indeks] != nullptr) {
            if(parovi[indeks] -> key == kljuc && !parovi[indeks] -> obrisan) {
                parovi[indeks] -> obrisan = true;
                broj_el--;
                return;
            }
        }
        else
            break;
    }
    throw "Kljuc ne postoji!";
}

#endif