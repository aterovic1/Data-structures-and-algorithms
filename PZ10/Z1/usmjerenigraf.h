#ifndef USMJERENIGRAF_H
#define USMJERENIGRAF_H

#include <vector>
#include <iomanip>
#include <iostream>

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
    UsmjereniGraf(int brCvorova) {}
    virtual ~UsmjereniGraf() {}
    virtual int dajBrojCvorova() const = 0;
    virtual void postaviBrojCvorova(int brCvorova) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina) = 0;
    virtual float dajTezinuGrane(int polazni, int dolazni) const = 0;
    virtual bool postojiGrana(int polazni, int dolazni) const = 0;
    virtual void postaviOznakuCvora(int cvor, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuCvora(int cvor) const = 0;
    virtual void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) = 0;
    virtual TipOznake dajOznakuGrane(int polazni, int dolazni) const = 0;
    Grana<TipOznake> dajGranu(int polazni, int dolazni);
    Cvor<TipOznake> dajCvor(int cvor);
    virtual GranaIterator<TipOznake> dajGranePocetak() = 0;
    virtual GranaIterator<TipOznake> dajGraneKraj() = 0;
    virtual GranaIterator<TipOznake> dajSljedecuGranu(int polazni, int dolazni) = 0;
    virtual void ispisiGraf() const = 0;
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
class MatricaGraf : public UsmjereniGraf<TipOznake> {
    struct OpisGrane {
        TipOznake oznaka;
        float tezina;
        OpisGrane(float t) : oznaka(TipOznake()), tezina(t) {}
        OpisGrane(TipOznake o, float t) : oznaka(o), tezina(t) {}
    };
    std::vector<std::vector<OpisGrane*>> matrica;
    std::vector<TipOznake> oznakeCv;
public:
    MatricaGraf(int brCvorova);
    ~MatricaGraf();
    MatricaGraf(const MatricaGraf<TipOznake>& mg);
    MatricaGraf<TipOznake>& operator =(const MatricaGraf<TipOznake>& mg);
    int dajBrojCvorova() const;
    void postaviBrojCvorova(int brCvorova);
    void dodajGranu(int polazni, int dolazni, float tezina);
    void obrisiGranu(int polazni, int dolazni);
    void postaviTezinuGrane(int polazni, int dolazni, float tezina);
    float dajTezinuGrane(int polazni, int dolazni) const;
    bool postojiGrana(int polazni, int dolazni) const;
    void postaviOznakuCvora(int cvor, TipOznake oznaka);
    TipOznake dajOznakuCvora(int cvor) const;
    void postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka);
    TipOznake dajOznakuGrane(int polazni, int dolazni) const;
    Grana<TipOznake> dajGranu(int polazni, int dolazni);
    Cvor<TipOznake> dajCvor(int cvor);
    GranaIterator<TipOznake> dajSljedecuGranu(int polazni, int dolazni);
    GranaIterator<TipOznake> dajGranePocetak();
    GranaIterator<TipOznake> dajGraneKraj();
};

template <typename TipOznake>
MatricaGraf<TipOznake>::MatricaGraf(int brCvorova) : UsmjereniGraf<TipOznake>(brCvorova) {
    matrica.resize(brCvorova);
    for(std::vector<OpisGrane*>& x : matrica)
        x.resize(brCvorova, nullptr);
    oznakeCv.resize(brCvorova);
}

template <typename TipOznake>
MatricaGraf<TipOznake>::~MatricaGraf() {
    for(std::vector<OpisGrane*>& x : matrica)
        for(OpisGrane*& g : x)
            if(g != nullptr)
                delete g;
}

template <typename TipOznake>
MatricaGraf<TipOznake>::MatricaGraf(const MatricaGraf<TipOznake>& mg) {
    oznakeCv = mg.oznakeCv;
    matrica.resize(mg.matrica.size());
    for(std::vector<OpisGrane*>& x : matrica)
        x.resize(mg.matrica.size(), nullptr);
    for(int i(0); i < mg.matrica.size(); i ++) 
        for(int j(0); j < mg.matrica.size(); j++) {
            if(mg.matrica[i][j] != nullptr)
                matrica[i][j] = new OpisGrane(mg.matrica[i][j] -> oznaka, mg.matrica[i][j] -> tezina);
            else
                matrica[i][j] = nullptr;
        }
}

template <typename TipOznake>
MatricaGraf<TipOznake>& MatricaGraf<TipOznake>::operator =(const MatricaGraf<TipOznake>& mg) {
    if(this == &mg)
        return *this;
    for(std::vector<OpisGrane*>& x : matrica)
        for(OpisGrane*& g : x)
            if(g != nullptr)
                delete g;
    oznakeCv = mg.oznakeCv;
    matrica.resize(mg.matrica.size());
    for(std::vector<OpisGrane*>& x : matrica)
        x.resize(mg.matrica.size(), nullptr);
    for(int i(0); i < mg.matrica.size(); i ++) 
        for(int j(0); j < mg.matrica.size(); j++) {
            if(mg.matrica[i][j] != nullptr)
                matrica[i][j] = new OpisGrane(mg.matrica[i][j] -> oznaka, mg.matrica[i][j] -> tezina);
            else
                matrica[i][j] = nullptr;
        }
    return *this;
}

template <typename TipOznake>
int MatricaGraf<TipOznake>::dajBrojCvorova() const {
    return matrica.size();
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviBrojCvorova(int brCvorova) {
    if(brCvorova < matrica.size())
        throw "Broj cvorova se ne moze smanjiti!";
    for(std::vector<OpisGrane*>& x : matrica)
        x.resize(brCvorova, nullptr);
    std::vector<OpisGrane*> prazanRed(brCvorova, nullptr);
    matrica.resize(brCvorova, prazanRed);
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::dodajGranu(int polazni, int dolazni, float tezina) {
    matrica[polazni][dolazni] = new OpisGrane(tezina);
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::obrisiGranu(int polazni, int dolazni) {
    delete matrica[polazni][dolazni];
    matrica[polazni][dolazni] = nullptr;
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviTezinuGrane(int polazni, int dolazni, float tezina) {
    matrica[polazni][dolazni] -> tezina = tezina;
}

template <typename TipOznake>
float MatricaGraf<TipOznake>::dajTezinuGrane(int polazni, int dolazni) const {
   return matrica[polazni][dolazni] -> tezina;
}

template <typename TipOznake>
bool MatricaGraf<TipOznake>::postojiGrana(int polazni, int dolazni) const {
    return matrica[polazni][dolazni] != nullptr;
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviOznakuCvora(int cvor, TipOznake oznaka) {
    oznakeCv[cvor] = oznaka;
}

template <typename TipOznake>
TipOznake MatricaGraf<TipOznake>::dajOznakuCvora(int cvor) const {
    return oznakeCv[cvor];
}

template <typename TipOznake>
void MatricaGraf<TipOznake>::postaviOznakuGrane(int polazni, int dolazni, TipOznake oznaka) {
    matrica[polazni][dolazni] -> oznaka = oznaka;
}

template <typename TipOznake>
TipOznake MatricaGraf<TipOznake>::dajOznakuGrane(int polazni, int dolazni) const {
    return matrica[polazni][dolazni] -> oznaka;
}

template <typename TipOznake>
GranaIterator<TipOznake> MatricaGraf<TipOznake>::dajSljedecuGranu(int polazni, int dolazni) {
    for(int i(polazni); i < matrica.size(); i++) {
        for(int j(0); j < matrica.size(); j++) {
            if(i == polazni && j <= dolazni)
                continue;
            if(matrica[i][j] != nullptr) {
                return GranaIterator<TipOznake>(this, i, j);
            }
        }
    }
    return GranaIterator<TipOznake>(this, -1, -1);
}

template <typename TipOznake>
GranaIterator<TipOznake> MatricaGraf<TipOznake>::dajGranePocetak() {
    GranaIterator<TipOznake> gIt(this, 0, -1);
    return ++gIt;
}

template <typename TipOznake>
GranaIterator<TipOznake> MatricaGraf<TipOznake>::dajGraneKraj() {
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