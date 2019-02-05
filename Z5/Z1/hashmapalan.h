#ifndef HASHMAPALAN_H
#define HASHMAPALAN_H

#include "mapa.h"
#include "dplista.h"

const int VEL = 1000;

template <typename TipK, typename TipV>
class HashMapaLan : public Mapa<TipK, TipV> {
    struct Par {
        TipK key;
        TipV value;
        Par(const TipK& kljuc, const TipV& vrijednost) : key(kljuc), value(vrijednost) {}
        Par(const TipK& kljuc) : key(kljuc), value(TipV()) {}
        Par(const Par& par) : key(par.key), value(par.value) {}
    };
    DvostrukaLista<Par>** parovi; //dvostruka lista zbog operacija prethodni() i dodajIza();
    int kapacitet;
    int broj_el;
    unsigned int (*h)(TipK, unsigned int);
public:
    HashMapaLan();
    ~HashMapaLan();
    HashMapaLan(const HashMapaLan<TipK, TipV>& hmapalan);
    HashMapaLan<TipK, TipV>& operator =(const HashMapaLan<TipK, TipV>& hmapalan);
    TipV operator [](const TipK& kljuc) const;
    TipV& operator [](const TipK& kljuc);
    int brojElemenata() const { return broj_el; }
    void obrisi();
    void obrisi(const TipK& kljuc);
    void definisiHashFunkciju(unsigned int (*f)(TipK, unsigned int)) { h = f; }
};

template <typename TipK, typename TipV>
HashMapaLan<TipK, TipV>::HashMapaLan() : Mapa<TipK, TipV>() {
    parovi = new DvostrukaLista<Par>*[VEL];
    kapacitet = VEL;
    broj_el = 0;
    h = nullptr;
    for(int i(0); i < kapacitet; i++)
        parovi[i] = nullptr;
}

template <typename TipK, typename TipV>
HashMapaLan<TipK, TipV>::~HashMapaLan() {
    for(int i(0); i < kapacitet; i++) {
        if(parovi[i] != nullptr) {
            parovi[i] -> obrisiListu();
            delete parovi[i];
        }
    }
    delete[] parovi;
}

template <typename TipK, typename TipV>
HashMapaLan<TipK, TipV>::HashMapaLan(const HashMapaLan<TipK, TipV>& hmapalan) {
    broj_el = hmapalan.broj_el;
    kapacitet = hmapalan.kapacitet;
    h = hmapalan.h;
    parovi = new DvostrukaLista<Par>*[kapacitet];
    for(int i(0); i < kapacitet; i++) {
        if(hmapalan.parovi[i] != nullptr) {
            parovi[i] = new DvostrukaLista<Par>();
            hmapalan.parovi[i] -> pocetak();
            for(int j(0); j < hmapalan.parovi[i] -> brojElemenata(); j++) {
                parovi[i] -> dodajIza(hmapalan.parovi[i] -> trenutni());
                hmapalan.parovi[i] -> sljedeci();
                if(j != 0)
                    parovi[i] -> sljedeci();
            }
        }
        else
            parovi[i] = nullptr;
    }
}

template <typename TipK, typename TipV>
HashMapaLan<TipK, TipV>& HashMapaLan<TipK, TipV>::operator =(const HashMapaLan<TipK, TipV>& hmapalan) {
    if(&hmapalan == this)
        return *this;
    for(int i(0); i < kapacitet; i++) {
        if(parovi[i] != nullptr) {
            parovi[i] -> obrisiListu();
            delete parovi[i];
        }
    }
    delete[] parovi;
    broj_el = hmapalan.broj_el;
    kapacitet = hmapalan.kapacitet;
    h = hmapalan.h;
    parovi = new DvostrukaLista<Par>*[kapacitet];
    for(int i(0); i < kapacitet; i++) {
        if(hmapalan.parovi[i] != nullptr) {
            parovi[i] = new DvostrukaLista<Par>();
            hmapalan.parovi[i] -> pocetak();
            for(int j(0); j < hmapalan.parovi[i] -> brojElemenata(); j++) {
                parovi[i] -> dodajIza(hmapalan.parovi[i] -> trenutni());
                hmapalan.parovi[i] -> sljedeci();
                if(j != 0)
                    parovi[i] -> sljedeci();
            }
        }
        else
            parovi[i] = nullptr;
    }
    return *this;
}

template <typename TipK, typename TipV>
TipV HashMapaLan<TipK, TipV>::operator [](const TipK& kljuc) const {
    if(!h)
        throw "GRESKA!";
        
    unsigned int hash = h(kljuc, kapacitet);
    if(parovi[hash] == nullptr)
        return TipV();
    //sekvencijalno pretrazujemo listu
    parovi[hash] -> pocetak();
    int i = 0;
    while(i < parovi[hash] -> brojElemenata() && parovi[hash] -> trenutni().key <= kljuc) {
        if(parovi[hash] -> trenutni().key == kljuc)
            return parovi[hash] -> trenutni().value;
        parovi[hash] -> sljedeci();
        i++;
    }
    return TipV();
}

template <typename TipK, typename TipV>
TipV& HashMapaLan<TipK, TipV>::operator [](const TipK& kljuc) {
    if(!h)
        throw "GRESKA!";
        
    unsigned int hash = h(kljuc, kapacitet);
    if(parovi[hash] == nullptr) {
        parovi[hash] = new DvostrukaLista<Par>();
        parovi[hash] -> dodajIza(Par(kljuc));
        broj_el++;
        return parovi[hash] -> trenutni().value;
    }
    parovi[hash] -> pocetak();
    int i = 0;
    while(i < parovi[hash] -> brojElemenata() && parovi[hash] -> trenutni().key <= kljuc) {
        if(parovi[hash] -> trenutni().key == kljuc)
            return parovi[hash] -> trenutni().value;
        i++;
        if(i == parovi[hash] -> brojElemenata()) {
            parovi[hash] -> dodajIza(Par(kljuc));
            broj_el++;
            parovi[hash] -> sljedeci();
            return parovi[hash] -> trenutni().value;
        }
        parovi[hash] -> sljedeci();
    }
    parovi[hash] -> dodajIspred(Par(kljuc));
    broj_el++;
    parovi[hash] -> prethodni();
    return parovi[hash] -> trenutni().value;
}

template <typename TipK, typename TipV>
void HashMapaLan<TipK, TipV>::obrisi() {
    for(int i(0); i < kapacitet; i++) {
        if(parovi[i] != nullptr) {
            parovi[i] -> obrisiListu();
            delete parovi[i];
            parovi[i] = nullptr;
        }
    }
    broj_el = 0;
}

template <typename TipK, typename TipV>
void HashMapaLan<TipK, TipV>::obrisi(const TipK& kljuc) {
    unsigned int hash = h(kljuc, kapacitet);
    if(parovi[hash] != nullptr) {
        parovi[hash] -> pocetak();
        int i = 0;
        while(i < parovi[hash] -> brojElemenata() && parovi[hash] -> trenutni().key <= kljuc) {
            if(parovi[hash] -> trenutni().key == kljuc) {
                parovi[hash] -> obrisi();
                broj_el--;
                if(parovi[hash] -> brojElemenata() == 0) {
                    delete parovi[hash];
                    parovi[hash] = nullptr;
                }
                return;
            }
            parovi[hash] -> sljedeci();
            i++;
        }
    }
    throw "Kljuc ne postoji!";
}

#endif