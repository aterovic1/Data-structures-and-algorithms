#ifndef DPLISTA_H
#define DPLISTA_H

#include "lista.h"

template <typename Tip>
class DvostrukaLista : public Lista<Tip> {
    struct Cvor {
        Tip element;
        Cvor* iduci;
        Cvor* prosli;
        Cvor(const Tip& el) : element(el), iduci(nullptr), prosli(nullptr) {}
    };
    int broj_el;
    Cvor* pocetni, *krajnji;
    Cvor* tekuci;
public:
    DvostrukaLista() : Lista<Tip>(), broj_el(0), pocetni(nullptr), krajnji(nullptr), tekuci(nullptr) {}
    ~DvostrukaLista() { obrisiListu(); }
    DvostrukaLista(const DvostrukaLista<Tip>& dpl);
    DvostrukaLista<Tip>& operator =(const DvostrukaLista<Tip>& dpl);
    int brojElemenata() const { return broj_el; }
    Tip& trenutni();
    Tip trenutni() const;
    bool prethodni();
    bool sljedeci();
    void pocetak();
    void kraj();
    void obrisi();
    Tip& operator [](int);
    Tip operator [](int) const;
    void dodajIspred(const Tip&);
    void dodajIza(const Tip&);
    void obrisiListu();
};

template<typename Tip>
void DvostrukaLista<Tip>::obrisiListu() {
    while(pocetni != nullptr) {
        tekuci = pocetni;
        pocetni = pocetni -> iduci;
        delete tekuci;
    }
    pocetni = tekuci = krajnji = nullptr;
    broj_el = 0;
}

template<typename Tip>
DvostrukaLista<Tip>::DvostrukaLista(const DvostrukaLista<Tip>& dpl) : broj_el(dpl.broj_el) {
    Cvor* tmp(dpl.pocetni), *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp1 == nullptr)
            pocetni = novi;
        else {
            tmp1 -> iduci = novi;
            novi -> prosli = tmp1;
        }
        tmp1 = novi;
        if(tmp == dpl.tekuci)
            tekuci = tmp1;
        tmp = tmp -> iduci;
    }
    krajnji = tmp1;
}

template<typename Tip>
DvostrukaLista<Tip>& DvostrukaLista<Tip>::operator =(const DvostrukaLista<Tip>& dpl) {
    if(this == &dpl) return *this;
    broj_el = dpl.broj_el;
    while(pocetni != nullptr) {
        tekuci = pocetni;
        pocetni = pocetni -> iduci;
        delete tekuci;
    }
    Cvor* tmp(dpl.pocetni), *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp1 == nullptr)
            pocetni = novi;
        else {
            tmp1 -> iduci = novi;
            novi -> prosli = tmp1;
        }
        tmp1 = novi;
        if(tmp == dpl.tekuci)
            tekuci = tmp1;
        tmp = tmp -> iduci;
    }
    krajnji = tmp1;
    return *this;
}

template<typename Tip>
Tip& DvostrukaLista<Tip>::trenutni() {
    if(broj_el == 0) throw "GRESKA! Lista je prazna!";
    return tekuci -> element;
}

template<typename Tip>
Tip DvostrukaLista<Tip>::trenutni() const {
    if(broj_el == 0) throw "GRESKA! Lista je prazna!";
    return tekuci -> element;
}

template<typename Tip>
bool DvostrukaLista<Tip>::prethodni() {
    if(broj_el == 0) throw "GRESKA! Lista je prazna!";
    if(tekuci == pocetni) return false;
    tekuci = tekuci -> prosli;
    return true;
}

template<typename Tip>
bool DvostrukaLista<Tip>::sljedeci() {
    if(broj_el == 0) throw "GRESKA! Lista je prazna!";
    if(tekuci == krajnji) return false;
    tekuci = tekuci -> iduci;
    return true;
}

template<typename Tip>
void DvostrukaLista<Tip>::pocetak() {
    if(broj_el == 0) throw "GRESKA! Lista je prazna!";
    tekuci = pocetni;
}

template<typename Tip>
void DvostrukaLista<Tip>::kraj() {
    if(broj_el == 0) throw "GRESKA! Lista je prazna!";
    tekuci = krajnji;
}

template<typename Tip>
void DvostrukaLista<Tip>::obrisi() {
    if(broj_el == 0) throw "GRESKA! Nista za obrisati!";
    Cvor* tmp(tekuci);
    if(pocetni == tekuci) {
        pocetni = tekuci = pocetni -> iduci;
        if(tekuci != nullptr)
            tekuci -> prosli = nullptr;
        if(krajnji == tmp)
            krajnji = nullptr;
    }
    else if(krajnji == tekuci) {
        krajnji = tekuci = krajnji -> prosli;
        tekuci -> iduci = nullptr;
    }
    else {
        tekuci -> prosli -> iduci = tekuci -> iduci;
        tekuci -> iduci -> prosli = tekuci -> prosli;
        tekuci = tmp -> iduci;
    }
    delete tmp;
    broj_el--;
}

template<typename Tip>
Tip& DvostrukaLista<Tip>::operator [](int i) {
    if(i < 0 || i >= broj_el) throw "GRESKA! Pristup tom clanu nije moguc!";
    if(i < broj_el / 2) {
        Cvor* poc(pocetni);
        for(int j(0); j < i; j++) 
            poc = poc -> iduci;
        return poc -> element;
    }
    else {
        Cvor* kr(krajnji);
        for(int j(broj_el - 1); j > i; j--)
            kr = kr -> prosli;
        return kr -> element;
    }
}

template<typename Tip>
Tip DvostrukaLista<Tip>::operator [](int i) const {
    if(i < 0 || i >= broj_el) throw "GRESKA! Pristup tom clanu nije moguc!";
    if(i < broj_el / 2) {
        Cvor* poc(pocetni);
        for(int j(0); j < i; j++) 
            poc = poc -> iduci;
        return poc -> element;
    }
    else {
        Cvor* kr(krajnji);
        for(int j(broj_el - 1); j > i; j--)
            kr = kr -> prosli;
        return kr -> element;
    }
}

template<typename Tip>
void DvostrukaLista<Tip>::dodajIspred(const Tip& el) {
    Cvor* novi = new Cvor(el);
    if(tekuci == pocetni) {
        novi -> iduci = tekuci;
        pocetni = novi;
        if(krajnji == nullptr)
            krajnji = novi;
        if(tekuci == nullptr)
            tekuci = novi;
        else 
            tekuci -> prosli = novi;
    }
    else {
        novi -> iduci = tekuci;
        novi -> prosli = tekuci -> prosli;
        tekuci -> prosli = novi;
        novi -> prosli -> iduci = novi;
    }
    broj_el++;
}

template<typename Tip>
void DvostrukaLista<Tip>::dodajIza(const Tip& el) {
    Cvor* novi = new Cvor(el);
    if(tekuci == krajnji) {
        novi -> prosli = tekuci;
        krajnji = novi;
        if(pocetni == nullptr)
            pocetni = novi;
        if(tekuci == nullptr)
            tekuci = novi;
        else
            tekuci -> iduci = novi;
    }
    else {
        novi -> prosli = tekuci;
        novi -> iduci = tekuci -> iduci;
        tekuci -> iduci = novi;
        novi -> iduci -> prosli = novi;
    }
    broj_el++;
}

#endif