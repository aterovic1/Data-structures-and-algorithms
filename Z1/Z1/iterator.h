#ifndef ITERATOR_H
#define ITERATOR_H

#include "dplista.h"

template <typename Tip>
class DvostrukaLista;

template <typename Tip>
class Iterator {
    const DvostrukaLista<Tip>* dl;
    typename DvostrukaLista<Tip>::Cvor* tekuci;
public:
    Iterator(const Lista<Tip>& l) { 
        dl = (const DvostrukaLista<Tip>*)&l;
        tekuci = dl -> pocetni;
    }
    Iterator(const DvostrukaLista<Tip>& dpl) : dl(&dpl), tekuci(dl -> pocetni) {}
    bool prethodni();
    bool sljedeci();
    void pocetak();
    void kraj();
    Tip& trenutni();
};

template <typename Tip>
bool Iterator<Tip>::prethodni() {
    if(dl -> broj_el == 0) throw "GRESKA! Lista je prazna!";
    if(tekuci == dl -> pocetni) return false;
    tekuci = tekuci -> prosli;
    return true;
}

template <typename Tip>
bool Iterator<Tip>::sljedeci() {
    if(dl -> broj_el == 0) throw "GRESKA! Lista je prazna!";
    if(tekuci == dl -> krajnji) return false;
    tekuci = tekuci -> iduci;
    return true;
}

template <typename Tip>
void Iterator<Tip>::pocetak() {
    if(dl -> broj_el == 0) throw "GRESKA! Lista je prazna!";
    tekuci = dl -> pocetni;
}

template <typename Tip>
void Iterator<Tip>::kraj() {
    if(dl -> broj_el == 0) throw "GRESKA! Lista je prazna!";
    tekuci = dl -> krajnji;
}

template <typename Tip>
Tip& Iterator<Tip>::trenutni() {
    if(dl -> broj_el == 0) throw "GRESKA! Lista je prazna!";
    return tekuci -> element;
}

template <typename Tip>
Tip dajMaksimum(const Lista<Tip>& n) {
    Iterator<Tip> it(n);
    Tip max = it.trenutni();
    it.sljedeci();
    for(int i(1); i < n.brojElemenata(); i++) {
        if(it.trenutni() > max) max = it.trenutni();
        it.sljedeci();
    }
    return max;
}

#endif