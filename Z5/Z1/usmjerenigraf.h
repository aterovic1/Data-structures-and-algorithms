#ifndef USMJERENIGRAF_H
#define USMJERENIGRAF_H

#include <vector>

#include "jplista.h"

template <typename TipOznake>
class Grana;

template <typename TipOznake>
class Cvor;

template <typename TipOznake>
class GranaIterator;


template <typename TipOznake>
class UsmjereniGraf {
    int brojCvorova;
public:
    UsmjereniGraf(int brCvorova) { brojCvorova = brCvorova; }
    virtual ~UsmjereniGraf() {}
    virtual int dajBrojCvorova() const = 0;
    virtual void postaviBrojCvorova(int brCvorova) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina) = 0;
    virtual float dajTezinuGrane(int polazni, int dolazni) = 0;
    virtual bool postojiGrana(int polazni, int dolazni) = 0;
    virtual void postaviOznakuCvora(int cvor, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuCvora(int cvor) const = 0;
    virtual void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuGrane(int polazni, int dolazni) = 0;
    Grana<TipOznake> dajGranu(int polazni, int dolazni);
    Cvor<TipOznake> dajCvor(int cvor);
    virtual GranaIterator<TipOznake> dajGranePocetak() = 0;
    virtual GranaIterator<TipOznake> dajGraneKraj() = 0;
    virtual GranaIterator<TipOznake> dajSljedecuGranu(int polazni, int dolazni) = 0;
};

template <typename TipOznake>
Grana<TipOznake> UsmjereniGraf<TipOznake>::dajGranu(int polazni, int dolazni) {
    return Grana<TipOznake>(this, polazni, dolazni);
}

template <typename TipOznake>
Cvor<TipOznake> UsmjereniGraf<TipOznake>::dajCvor(int cvor) {
    return Cvor<TipOznake>(this, cvor);
}

//******************************************************************************

template <typename TipOznake>
class ListaGraf : public UsmjereniGraf<TipOznake> {
    struct OpisGrane {
        TipOznake oznaka;
        float tezina;
        int brojDolaznogCvora;
        OpisGrane(float t, int d) : oznaka(TipOznake()), tezina(t), brojDolaznogCvora(d) {}
        OpisGrane(TipOznake o, float t) : oznaka(o), tezina(t) {}
    };
    std::vector<JednostrukaLista<OpisGrane>*> listeSusjedstva;
    std::vector<TipOznake> oznakeCv;
public:
    ListaGraf(int brCvorova);
    ~ListaGraf();
    int dajBrojCvorova() const;
    void postaviBrojCvorova(int brCvorova);
    void dodajGranu(int polazni, int dolazni, float tezina);
    void obrisiGranu(int polazni, int dolazni);
    void postaviTezinuGrane(int polazni, int dolazni, float tezina);
    float dajTezinuGrane(int polazni, int dolazni);
    bool postojiGrana(int polazni, int dolazni);
    void postaviOznakuCvora(int cvor, TipOznake oznaka);
    TipOznake dajOznakuCvora(int cvor) const;
    void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka);
    TipOznake dajOznakuGrane(int polazni, int dolazni);
    Grana<TipOznake> dajGranu(int polazni, int dolazni);
    Cvor<TipOznake> dajCvor(int cvor);
    GranaIterator<TipOznake> dajSljedecuGranu(int polazni, int dolazni);
    GranaIterator<TipOznake> dajGranePocetak();
    GranaIterator<TipOznake> dajGraneKraj();
};

template <typename TipOznake>
ListaGraf<TipOznake>::ListaGraf(int brCvorova) : UsmjereniGraf<TipOznake>(brCvorova) {
    oznakeCv.resize(brCvorova);
    listeSusjedstva.resize(brCvorova, nullptr);
}

template <typename TipOznake>
ListaGraf<TipOznake>::~ListaGraf() {
    for(int i(0); i < listeSusjedstva.size(); i++) 
        delete listeSusjedstva[i];
}

template <typename TipOznake>
int ListaGraf<TipOznake>::dajBrojCvorova() const {
    return listeSusjedstva.size();
}

template <typename TipOznake>
void ListaGraf<TipOznake>::postaviBrojCvorova(int brCvorova) {
    if(brCvorova < listeSusjedstva.size())
        throw "Broj cvorova se ne moze smanjiti!";
    listeSusjedstva.resize(brCvorova, nullptr);
}

template <typename TipOznake>
void ListaGraf<TipOznake>::dodajGranu(int polazni, int dolazni, float tezina) {
    int i = 0;
    if(listeSusjedstva[polazni] == nullptr)
        listeSusjedstva[polazni] = new JednostrukaLista<OpisGrane>; //std::cout << listeSusjedstva[polazni] -> brojElemenata() << " <-\n";
    else
        listeSusjedstva[polazni] -> pocetak();
    while(i < listeSusjedstva[polazni] -> brojElemenata() && listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora <= dolazni) {
        i++;
        if(i == listeSusjedstva[polazni] -> brojElemenata()) {
            listeSusjedstva[polazni] -> dodajIza(OpisGrane(tezina, dolazni));
            return;
        }
        listeSusjedstva[polazni] -> sljedeci();
    }
    listeSusjedstva[polazni] -> dodajIspred(OpisGrane(tezina, dolazni));
}

template <typename TipOznake>
void ListaGraf<TipOznake>::obrisiGranu(int polazni, int dolazni) {
    listeSusjedstva[polazni] -> pocetak();
    while(listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora != dolazni)
        listeSusjedstva[polazni] -> sljedeci();
    listeSusjedstva[polazni] -> obrisi();
}

template <typename TipOznake>
void ListaGraf<TipOznake>::postaviTezinuGrane(int polazni, int dolazni, float tezina) {
    listeSusjedstva[polazni] -> pocetak();
    while(listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora != dolazni)
        listeSusjedstva[polazni] -> sljedeci();
    listeSusjedstva[polazni] -> trenutni().tezina = tezina;
}

template <typename TipOznake>
float ListaGraf<TipOznake>::dajTezinuGrane(int polazni, int dolazni) {
    listeSusjedstva[polazni] -> pocetak();
    while(listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora != dolazni)
        listeSusjedstva[polazni] -> sljedeci();
    return listeSusjedstva[polazni] -> trenutni().tezina;
}

template <typename TipOznake>
bool ListaGraf<TipOznake>::postojiGrana(int polazni, int dolazni) {
    if(listeSusjedstva[polazni] == nullptr)
        return false;
    listeSusjedstva[polazni] -> pocetak();
    int i = 0;
    while(i < listeSusjedstva[polazni] -> brojElemenata()) {
        if(listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora == dolazni)
            return true;
        listeSusjedstva[polazni] -> sljedeci();
        i++;
    }
    return false;
}

template <typename TipOznake>
void ListaGraf<TipOznake>::postaviOznakuCvora(int cvor, TipOznake oznaka) {
    oznakeCv[cvor] = oznaka;
}

template <typename TipOznake>
TipOznake ListaGraf<TipOznake>::dajOznakuCvora(int cvor) const {
    return oznakeCv[cvor];
}

template <typename TipOznake>
void ListaGraf<TipOznake>::postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) {
    listeSusjedstva[polazni] -> pocetak();
    while(listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora != dolazni)
        listeSusjedstva[polazni] -> sljedeci();
    listeSusjedstva[polazni] -> trenutni().oznaka = oznaka;
}

template <typename TipOznake>
TipOznake ListaGraf<TipOznake>::dajOznakuGrane(int polazni, int dolazni) {
    listeSusjedstva[polazni] -> pocetak();
    while(listeSusjedstva[polazni] -> trenutni().brojDolaznogCvora != dolazni)
        listeSusjedstva[polazni] -> sljedeci();
    return listeSusjedstva[polazni] -> trenutni().oznaka;
}

template <typename TipOznake>
GranaIterator<TipOznake> ListaGraf<TipOznake>::dajSljedecuGranu(int polazni, int dolazni) {
    for(int i(polazni); i < listeSusjedstva.size(); i++) {
        if(listeSusjedstva[i] == nullptr)
            continue;
        int j = 0;
        listeSusjedstva[i] -> pocetak();
        while(j < listeSusjedstva[i] -> brojElemenata()) {
            if(i == polazni && listeSusjedstva[i] -> trenutni().brojDolaznogCvora <= dolazni) {
                listeSusjedstva[i] -> sljedeci();
                j++;
                continue;
            }
            return GranaIterator<TipOznake>(this, i, listeSusjedstva[i] -> trenutni().brojDolaznogCvora);
        }
    }
    return GranaIterator<TipOznake>(this, -1, -1);
}

template <typename TipOznake>
GranaIterator<TipOznake> ListaGraf<TipOznake>::dajGranePocetak() {
    GranaIterator<TipOznake> gIt(this, 0, -1);
    return ++gIt;
}

template <typename TipOznake>
GranaIterator<TipOznake> ListaGraf<TipOznake>::dajGraneKraj() {
    GranaIterator<TipOznake> gIt(this, -1, -1);
    return gIt;
}

//******************************************************************************

template <typename TipOznake> 
class Grana {
    UsmjereniGraf<TipOznake>* graf; //zbog polimorfizma
    int polazni, dolazni;
public:
    Grana(UsmjereniGraf<TipOznake>* g, int p, int d) : graf(g), polazni(p), dolazni(d) {}
    float dajTezinu() const { return graf -> dajTezinuGrane(polazni, dolazni); }
    void postaviTezinu(float tezina) { graf -> postaviTezinuGrane(polazni, dolazni, tezina); }
    TipOznake dajOznaku() const { return graf -> dajOznakuGrane(polazni, dolazni); }
    void postaviOznaku(TipOznake oznaka) { graf -> postaviOznakuGrane(polazni, dolazni, oznaka); }
    Cvor<TipOznake> dajPolazniCvor() const { return graf -> dajCvor(polazni); }
    Cvor<TipOznake> dajDolazniCvor() const { return graf -> dajCvor(dolazni); }
};

//******************************************************************************

template <typename TipOznake>
class Cvor {
    UsmjereniGraf<TipOznake>* graf;
    int redniBroj;
public:
    Cvor(UsmjereniGraf<TipOznake>* g, int redniBr) : graf(g), redniBroj(redniBr) {}
    TipOznake dajOznaku() const { return graf -> dajOznakuCvora(redniBroj); }
    void postaviOznaku(TipOznake oznaka) { graf -> postaviOznakuCvora(redniBroj, oznaka); }
    int dajRedniBroj() const { return redniBroj; }
};

//******************************************************************************

template <typename TipOznake>
class GranaIterator {
    UsmjereniGraf<TipOznake>* graf;
    int polazni, dolazni;
    bool postoji;
public:
    GranaIterator(UsmjereniGraf<TipOznake>* g, int p, int d) : graf(g), polazni(p), dolazni(d) {}
    Grana<TipOznake> operator *();
    bool operator ==(const GranaIterator& gIt) const;
    bool operator !=(const GranaIterator& gIt) const;
    GranaIterator& operator ++();
    GranaIterator operator ++(int);
    friend class Grana<TipOznake>;
};

template <typename TipOznake>
Grana<TipOznake> GranaIterator<TipOznake>::operator *() {
    return Grana<TipOznake>(graf, polazni, dolazni);
}

template <typename TipOznake>
bool GranaIterator<TipOznake>::operator ==(const GranaIterator<TipOznake>& gIt) const {
    return(graf == gIt.graf && polazni == gIt.polazni && dolazni == gIt.dolazni);
}

template <typename TipOznake>
bool GranaIterator<TipOznake>::operator !=(const GranaIterator<TipOznake>& gIt) const {
    return !(*this == gIt);
}

template <typename TipOznake>
GranaIterator<TipOznake>& GranaIterator<TipOznake>::operator ++() {
    if(polazni == -1 && dolazni == -1)
        throw "Nedozvoljena pozicija";
    GranaIterator<TipOznake> g = graf -> dajSljedecuGranu(polazni, dolazni);
    polazni = g.polazni;
    dolazni = g.dolazni;
    return *this;
}

template <typename TipOznake>
GranaIterator<TipOznake> GranaIterator<TipOznake>::operator ++(int) {
    GranaIterator<TipOznake> pom(*this);
    ++(*this);
    return pom;
}

#endif