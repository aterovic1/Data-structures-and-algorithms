#ifndef JPLISTA_H
#define JPLISTA_H

#include "lista.h"

template <typename Tip>
class JednostrukaLista : public Lista<Tip> {
    struct Cvor {
        Tip element;
        Cvor *sljedeci;
        Cvor(Tip el) : element(el), sljedeci(nullptr) {}
    };
    Cvor *pocetni, *krajnji;
    Cvor *tekuci;
    int brElemenata;
public:
    JednostrukaLista() : Lista<Tip>(), pocetni(nullptr), krajnji(nullptr), tekuci(nullptr), brElemenata(0) {}
    ~JednostrukaLista() { obrisiListu(); }
    JednostrukaLista(const JednostrukaLista<Tip>& l);
    JednostrukaLista<Tip>& operator =(const JednostrukaLista<Tip>& l);
    int brojElemenata() const { return brElemenata; }
    Tip& operator [](int i);
    Tip operator [](int i) const;
    Tip& trenutni();
    Tip trenutni() const;
    bool prethodni();
    bool sljedeci(); 
    void pocetak();
    void kraj();
    void obrisi();
    void dodajIspred(const Tip& el);
    void dodajIza(const Tip& el);
    void obrisiListu();
};

template <typename Tip>
void JednostrukaLista<Tip>::obrisiListu() {
    while(pocetni != nullptr) {
        tekuci = pocetni;
        pocetni = pocetni -> sljedeci;
        delete tekuci;
    }
    pocetni = krajnji = tekuci = nullptr;
    brElemenata = 0;
}

template <typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista<Tip>& l) {
    Cvor* tmp(l.pocetni), *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi(new Cvor(tmp -> element));
        if(tmp1 == nullptr)
            pocetni = novi;
        else
            tmp1 -> sljedeci = novi;
        tmp1 = novi;
        if(tmp == l.tekuci)
            tekuci = tmp1;
        tmp = tmp -> sljedeci;
    }
    krajnji = tmp1;
    brElemenata = l.brElemenata;
}

template <typename Tip>
JednostrukaLista<Tip>& JednostrukaLista<Tip>::operator =(const JednostrukaLista<Tip>& l) {
    if(this == &l) return *this;
    while(pocetni != nullptr) {
        tekuci = pocetni;
        pocetni = pocetni -> sljedeci;
        delete tekuci;
    }
    Cvor* tmp(l.pocetni), *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi(new Cvor(tmp -> element));
        if(tmp1 == nullptr)
            pocetni = novi;
        else
            tmp1 -> sljedeci = novi;
        tmp1 = novi;
        if(tmp == l.tekuci)
            tekuci = tmp1;
        tmp = tmp -> sljedeci;
    }
    krajnji = tmp1;
    brElemenata = l.brElemenata;
    return *this;
}

template <typename Tip>
Tip& JednostrukaLista<Tip>::operator [](int i) {
    if(i < 0 || i >= brElemenata) throw "GRESKA!"; 
    Cvor* tmp(pocetni);
    for(int j(0); j < i; j++)
        tmp = tmp -> sljedeci;
    return tmp -> element;
}

template <typename Tip>
Tip JednostrukaLista<Tip>::operator [](int i) const {
    if(i < 0 || i >= brElemenata) throw "GRESKA!";
    Cvor* tmp(pocetni);
    for(int j(0); j < i; j++)
        tmp = tmp -> sljedeci;
    return tmp -> element;
}

template <typename Tip>
Tip& JednostrukaLista<Tip>::trenutni() {
    if(pocetni == nullptr)
        throw "GRESKA!";
    return tekuci -> element;
}

template <typename Tip>
Tip JednostrukaLista<Tip>::trenutni() const {
    if(pocetni == nullptr) 
        throw "GRESKA!";
    return tekuci -> element;
}

template <typename Tip>
bool JednostrukaLista<Tip>::prethodni() {
    if(pocetni == nullptr) throw "GRESKA!";
    if(tekuci == pocetni) return false;
    Cvor* tmp(pocetni);
    while(tmp -> sljedeci != tekuci)
        tmp = tmp -> sljedeci;
    tekuci = tmp;
    return true;
}

template <typename Tip>
bool JednostrukaLista<Tip>::sljedeci() {
    if(pocetni == nullptr) throw "GRESKA!";
    if(tekuci -> sljedeci == nullptr) return false;
    tekuci = tekuci -> sljedeci;
    return true;
}

template <typename Tip>
void JednostrukaLista<Tip>::pocetak() {
    if(pocetni == nullptr)
        throw "GRESKA!";
    tekuci = pocetni;
}

template <typename Tip>
void JednostrukaLista<Tip>::kraj() {
    if(pocetni == nullptr)
        throw "GRESKA!";
    tekuci = krajnji;
}

template <typename Tip>
void JednostrukaLista<Tip>::obrisi() {
    if(pocetni == nullptr) throw "GRESKA!";
    if(tekuci == pocetni) {
        pocetni = pocetni -> sljedeci;
        delete tekuci;
        tekuci = pocetni;
        brElemenata--;
        if(brElemenata == 0) krajnji = nullptr;
        return;
    }
    Cvor* tmp(pocetni);
    while(tmp -> sljedeci != tekuci)
        tmp = tmp -> sljedeci;
    tmp -> sljedeci = tekuci -> sljedeci;
    delete tekuci;
    tekuci = tmp -> sljedeci;
    if(tekuci == nullptr) krajnji = tekuci = tmp;
    brElemenata--;
}

template <typename Tip>
void JednostrukaLista<Tip>::dodajIspred(const Tip& el) {
    Cvor* novi(new Cvor(el));
    brElemenata++;
    if(brElemenata == 1) 
        pocetni = krajnji = tekuci = novi;
    else if(tekuci == pocetni) {
        pocetni = novi;
        novi -> sljedeci = tekuci;
    }
    else {
        Cvor* tmp(pocetni);
        while(tmp -> sljedeci != tekuci)
            tmp = tmp -> sljedeci;
        tmp -> sljedeci = novi;
        novi -> sljedeci = tekuci;
    }
}

template <typename Tip>
void JednostrukaLista<Tip>::dodajIza(const Tip& el) {
    Cvor* novi(new Cvor(el));
    brElemenata++;
    if(brElemenata == 1)
        pocetni = krajnji = tekuci = novi;
    else {
        novi -> sljedeci = tekuci -> sljedeci;
        tekuci -> sljedeci = novi;
        if(tekuci == krajnji)
            krajnji = novi;
    }
}

#endif