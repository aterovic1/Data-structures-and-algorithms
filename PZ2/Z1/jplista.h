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
    ~JednostrukaLista();
    JednostrukaLista(const JednostrukaLista<Tip>& l);
    JednostrukaLista<Tip>& operator =(const JednostrukaLista<Tip>& l);
    int BrojElemenata() const {
        return brElemenata;
    }
    Tip& operator [](int i);
    Tip operator [](int i) const;
    Tip& trenutni() {
        if(pocetni == nullptr) throw "GRESKA!";
        return tekuci -> element;
    }
    Tip trenutni() const {
        if(pocetni == nullptr) throw "GRESKA!";
        return tekuci -> element;
    }
    bool prethodni();
    bool sljedeci(); 
    void pocetak() {
        if(pocetni == nullptr) throw "GRESKA!";
        tekuci = pocetni;
    }
    void kraj() {
        if(pocetni == nullptr) throw "GRESKA!";
        tekuci = krajnji;
    }
    void obrisi();
    void dodajIspred(const Tip& el);
    void dodajIza(const Tip& el);
};

#endif