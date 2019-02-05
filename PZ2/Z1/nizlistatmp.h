#ifndef NIZLISTATMP_H
#define NIZLISTATMP_H

#include "nizlista.h"
#include <algorithm>

template <typename Tip>
NizLista<Tip>::NizLista(const NizLista<Tip>& n) {
    kapacitet = n.kapacitet;
    brojElemenata = n.brojElemenata;
    tren = n.tren;
    L = new Tip[n.kapacitet];
    std::copy(n.L, n.L + kapacitet, L);
}

template <typename Tip>
NizLista<Tip>& NizLista<Tip>::operator =(const NizLista<Tip>& n) {
    if(&n == this) return *this;
    delete[] L;
    kapacitet = n.kapacitet;
    brojElemenata = n.brojElemenata;
    tren = n.tren;
    L = new Tip[n.kapacitet];
    std::copy(n.L, n.L + kapacitet, L);
}

template <typename Tip>
void NizLista<Tip>::obrisi() {
    if(brojElemenata == 0) throw "GRESKA!";
    brojElemenata--;
    for(int i(tren); i < brojElemenata; i++) 
        L[i] = L[i + 1];
    if(tren == brojElemenata && brojElemenata > 0) tren--;
}

template <typename Tip>
void NizLista<Tip>::dodajIspred(const Tip& el) {
    if(brojElemenata == kapacitet) {
        kapacitet *= 2;
        Tip *L1 = new Tip[kapacitet];
        std::copy(L, L + brojElemenata, L1);
        delete[] L;
        L = L1;
    }
    for(int i(brojElemenata); i > tren; i--)
        L[i] = L[i - 1];
    L[tren] = el;
    if(brojElemenata != 0) tren++;
    brojElemenata++;
}

template <typename Tip>
void NizLista<Tip>::dodajIza(const Tip& el) {
    if(brojElemenata == kapacitet) {
        kapacitet *= 2;
        Tip *L1 = new Tip[kapacitet];
        std::copy(L, L + brojElemenata, L1);
        delete[] L;
        L = L1;
    }
    for(int i(brojElemenata); i > tren + 1; i--)
        L[i] = L[i - 1];
    L[tren + 1] = el;
    brojElemenata++;
}

#endif