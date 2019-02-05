#ifndef BINSTABLOMAPA_H
#define BINSTABLOMAPA_H

#include "mapa.h"
//#include <iostream>

template <typename TipK, typename TipV>
class BinStabloMapa : public Mapa<TipK, TipV> {
    struct Cvor {
        TipK kljuc;
        TipV vrijednost;
        Cvor* lijevi, *desni;
        Cvor* roditelj;
        Cvor(const TipK& k, const TipV& v, Cvor* r) : kljuc(k), vrijednost(v), lijevi(nullptr), desni(nullptr), roditelj(r) {}
    };
    Cvor* korijen;
    int broj_el;
    
    Cvor* trazi(Cvor* cvor, const TipK& kljuc) const {
        if(cvor == nullptr || cvor -> kljuc == kljuc)
            return cvor;
        if(kljuc < cvor -> kljuc)
            return trazi(cvor -> lijevi, kljuc);
        return trazi(cvor -> desni, kljuc);
    }
    void obrisiStablo(Cvor* cvor);
    void kopirajStablo(Cvor*& cvor1, Cvor* cvor2, Cvor* roditelj1);
public:
    BinStabloMapa() : Mapa<TipK, TipV>(), korijen(nullptr), broj_el(0) {}
    ~BinStabloMapa();
    BinStabloMapa(const BinStabloMapa<TipK, TipV>& bsmapa);
    BinStabloMapa<TipK, TipV>& operator =(const BinStabloMapa<TipK, TipV>& bsmapa);
    TipV operator [](const TipK& kljuc) const;
    TipV& operator [](const TipK& kljuc);
    int brojElemenata() const { return broj_el; }
    void obrisi();
    void obrisi(const TipK& kljuc);
};

template <typename TipK, typename TipV>
BinStabloMapa<TipK, TipV>::~BinStabloMapa() {
    obrisiStablo(korijen);
}

template <typename TipK, typename TipV>
BinStabloMapa<TipK, TipV>::BinStabloMapa(const BinStabloMapa<TipK, TipV>& bsmapa) : korijen(nullptr), broj_el(0) {
    kopirajStablo(korijen, bsmapa.korijen, nullptr);
}

template <typename TipK, typename TipV>
BinStabloMapa<TipK, TipV>& BinStabloMapa<TipK, TipV>::operator =(const BinStabloMapa<TipK, TipV>& bsmapa) {
    if(this == &bsmapa)
        return *this;
    obrisiStablo(korijen);
    korijen = nullptr;
    broj_el = 0;
    kopirajStablo(korijen, bsmapa.korijen, nullptr);
    return *this;
}

template <typename TipK, typename TipV>
TipV BinStabloMapa<TipK, TipV>::operator [](const TipK& kljuc) const {
    Cvor* cvor = korijen;
    while(cvor != nullptr) {
        if(cvor -> kljuc == kljuc)
            return cvor -> vrijednost;
        else if(kljuc < cvor -> kljuc)
            cvor = cvor -> lijevi;
        else
            cvor = cvor -> desni;
    }
    return TipV();
}

template <typename TipK, typename TipV>
TipV& BinStabloMapa<TipK, TipV>::operator [](const TipK& kljuc) {
    Cvor* cvor = korijen;
    Cvor* rod = nullptr;
    while(cvor != nullptr) {
        if(cvor -> kljuc == kljuc)
            return cvor -> vrijednost;
        rod = cvor;
        if(kljuc < cvor -> kljuc) 
            cvor = cvor -> lijevi;
        else
            cvor = cvor -> desni;
    }
    if(rod == nullptr) {
        korijen = new Cvor(kljuc, TipV(), nullptr);
        broj_el++;
        return korijen -> vrijednost;
    }
    else {
        if(kljuc < rod -> kljuc) {
            rod -> lijevi = new Cvor(kljuc, TipV(), rod);
            broj_el++;
            return rod -> lijevi -> vrijednost;
        }
        else {
            rod -> desni = new Cvor(kljuc, TipV(), rod);
            broj_el++;
            return rod -> desni -> vrijednost;
        }
    }
}

template <typename TipK, typename TipV>
void BinStabloMapa<TipK, TipV>::obrisi() {
    obrisiStablo(korijen);
    korijen = nullptr;
    broj_el = 0;
}

template <typename TipK, typename TipV>
void BinStabloMapa<TipK, TipV>::obrisi(const TipK& kljuc) { 
    Cvor* del = trazi(korijen, kljuc); 
    if(del == nullptr)
        throw "Kljuc ne postoji!";
    if(del -> lijevi == nullptr && del -> desni == nullptr) { //ako cvor nema djece
        if(del == korijen) 
            korijen = nullptr;
        else if(del == del -> roditelj -> lijevi)
            del -> roditelj -> lijevi = nullptr;
        else
            del -> roditelj -> desni = nullptr;
        delete del;
    }
    else if(del -> lijevi != nullptr && del -> desni != nullptr) { //ako cvor ima oba djeteta
        //trazimo najdesniji(najveci) cvor u lijevom podstablu
        Cvor* pom = del -> lijevi;
        while(pom -> desni != nullptr)
            pom = pom -> desni;
        //najdesniji cvor uzima desno podstablo cvora kojeg brisemo
        pom -> desni = del -> desni;
        //azuriramo roditelja
        if(del -> desni != nullptr)
            del -> desni -> roditelj = pom;
        //roditelj najdesnijeg cvora kao svoje desno podstablo preuzima lijevo podstablo najdesnijeg
        pom -> roditelj -> desni = pom -> lijevi;
        //azuriramo roditelja
        if(pom -> lijevi != nullptr)
            pom -> lijevi -> roditelj = pom -> roditelj;
        //roditelj obrisanog preuzima najdesniji cvor uz provjeru da li brisemo korijen koji nema roditelja
        if(del == korijen) {
            korijen = pom;
        }
        else if(del == del -> roditelj -> lijevi) {
            del -> roditelj -> lijevi = pom;
            pom -> roditelj = del -> roditelj;
        }
        else {
            del -> roditelj -> desni = pom;
            pom -> roditelj = del -> roditelj;
        }
        //najdesniji cvor sada preuzima i lijevo podstablo cvora kojeg brisemo
        if(del == korijen)
            pom -> lijevi = nullptr;
        else {
            pom -> lijevi = del -> lijevi;
            del -> lijevi -> roditelj = pom;
        }
        delete del;
    }
    else { //ako cvor ima jedno dijete
        //da li cvor ima lijevo ili desno dijete?
        Cvor* dijete = del -> lijevi;
        if(dijete == nullptr)
            dijete = del -> desni;
        //ako brisemo korijen
        if(del == korijen) 
            korijen = dijete;
        //ako nije, preusmjerimo roditelja cvora koji se brise na njegovo dijete
        else if(del == del -> roditelj -> lijevi)
            del -> roditelj -> lijevi = dijete;
        else
            del -> roditelj -> desni = dijete;
        dijete -> roditelj = del -> roditelj;
        delete del;
    }
    broj_el--; 
}

template <typename TipK, typename TipV>
void BinStabloMapa<TipK, TipV>::obrisiStablo(Cvor* cvor) {
    if(cvor == nullptr)
        return;
    obrisiStablo(cvor -> lijevi);
    obrisiStablo(cvor -> desni);
    delete cvor;
}

template <typename TipK, typename TipV>
void BinStabloMapa<TipK, TipV>::kopirajStablo(Cvor*& cvor1, Cvor* cvor2, Cvor* roditelj1) {
    if(cvor2 == nullptr)
        return;
    cvor1 = new Cvor(cvor2 -> kljuc, cvor2 -> vrijednost, roditelj1);
    kopirajStablo(cvor1 -> lijevi, cvor2 -> lijevi, cvor1);
    kopirajStablo(cvor1 -> desni, cvor2 -> desni, cvor1);
    broj_el++;
}

#endif