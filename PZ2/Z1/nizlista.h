#ifndef NIZLISTA_H
#define NIZLISTA_H

#include "lista.h"
const int VEL = 1000;

template <typename Tip>
class NizLista : public Lista<Tip> {
    Tip *L;
    int kapacitet;
    int brojElemenata;
    int tren;
public:
    NizLista() : Lista<Tip>(), L(new Tip[VEL]), kapacitet(VEL), brojElemenata(0), tren(0) {}
    ~NizLista() { 
        delete[] L; 
    }
    NizLista(const NizLista<Tip>& n);
    NizLista<Tip>& operator =(const NizLista<Tip>& n);
    int BrojElemenata() const {
        return brojElemenata;
    }
    Tip& operator [](int i) {
        if(i < 0 || i >= brojElemenata) throw "GRESKA!";
        return L[i];
    }
    Tip operator [](int i) const {
        if(i < 0 || i >= brojElemenata) throw "GRESKA!";
        return L[i];
    }
    Tip& trenutni() {
        if(brojElemenata == 0) throw "GRESKA!";
        return L[tren];
    }
    Tip trenutni() const {
        if(brojElemenata == 0) throw "GRESKA!";
        return L[tren];
    }
    bool prethodni() {
        if(brojElemenata == 0) throw "GRESKA!";
        if(tren == 0) return false;
        tren--;
        return true;
    }
    bool sljedeci() {
        if(brojElemenata == 0) throw "GRESKA!";
        if(tren == brojElemenata - 1) return false;
        tren++;
        return true;
        
    }
    void pocetak() {
        if(brojElemenata == 0) throw "GRESKA!";
        tren = 0;
    }
    void kraj() {
        if(brojElemenata == 0) throw "GRESKA!";
        tren = brojElemenata - 1;
    }
    void obrisi();
    void dodajIspred(const Tip& el);
    void dodajIza(const Tip& el);
};

#endif