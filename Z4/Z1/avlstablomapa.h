#ifndef AVLSTABLOMAPA_H
#define AVLSTABLOMAPA_H

#include "mapa.h"
#include <iostream>
#include <string>

template <typename TipK, typename TipV>
class AVLStabloMapa : public Mapa<TipK, TipV> {
    struct Cvor {
        TipK kljuc;
        TipV vrijednost;
        Cvor* lijevi, *desni;
        Cvor* roditelj;
        int balans;
        Cvor(const TipK& k, const TipV& v, Cvor* r, int b) : kljuc(k), vrijednost(v), lijevi(nullptr), desni(nullptr), roditelj(r), balans(b) {}
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
    Cvor* dodaj(Cvor*& cvor, const TipK& kljuc, Cvor* rod) {
        if(cvor == nullptr) {
            cvor = new Cvor(kljuc, TipV(), rod, 0);
            broj_el++;
            return cvor;
        }
        else if(kljuc < cvor -> kljuc)
            return dodaj(cvor -> lijevi, kljuc, cvor);
        else
            return dodaj(cvor -> desni, kljuc, cvor);
    }
    void obrisiStablo(Cvor* cvor);
    void kopirajStablo(Cvor*& cvor1, Cvor* cvor2, Cvor* roditelj1);
    void azurirajBalans(Cvor* cvor);
    void jednostrukaLijevaRotacija(Cvor* cvor);
    void jednostrukaDesnaRotacija(Cvor* cvor);
    void ispisi(Cvor* c); //pomocna, koristena za testiranje
public:
    AVLStabloMapa() : Mapa<TipK, TipV>(), korijen(nullptr), broj_el(0) {}
    ~AVLStabloMapa();
    AVLStabloMapa(const AVLStabloMapa<TipK, TipV>& avlsmapa);
    AVLStabloMapa<TipK, TipV>& operator =(const AVLStabloMapa<TipK, TipV>& avlsmapa);
    TipV operator [](const TipK& kljuc) const;
    TipV& operator [](const TipK& kljuc);
    int brojElemenata() const { return broj_el; }
    void obrisi();
    void obrisi(const TipK& kljuc);
    void ispis(); //za testiranje
};

template <typename TipK, typename TipV>
AVLStabloMapa<TipK, TipV>::~AVLStabloMapa() {
    obrisiStablo(korijen);
}

template <typename TipK, typename TipV>
AVLStabloMapa<TipK, TipV>::AVLStabloMapa(const AVLStabloMapa<TipK, TipV>& avlsmapa) : korijen(nullptr), broj_el(0) {
    kopirajStablo(korijen, avlsmapa.korijen, nullptr);
}

template <typename TipK, typename TipV>
AVLStabloMapa<TipK, TipV>& AVLStabloMapa<TipK, TipV>::operator =(const AVLStabloMapa<TipK, TipV>& avlsmapa) {
    if(this == &avlsmapa)
        return *this;
    obrisiStablo(korijen);
    korijen = nullptr;
    broj_el = 0;
    kopirajStablo(korijen, avlsmapa.korijen, nullptr);
    return *this;
}

template <typename TipK, typename TipV>
TipV AVLStabloMapa<TipK, TipV>::operator [](const TipK& kljuc) const {
    Cvor* cvor = trazi(korijen, kljuc);
    if(cvor != nullptr)
        return cvor -> vrijednost;
    return TipV();
}

template <typename TipK, typename TipV>
TipV& AVLStabloMapa<TipK, TipV>::operator [](const TipK& kljuc) {
    Cvor* cvor = trazi(korijen, kljuc);
    if(cvor != nullptr)
        return cvor -> vrijednost;
    cvor = dodaj(korijen, kljuc, nullptr);
    //provjera balansa, ako cvor ima brata, balans roditelja cvora koji je bio 1 ili -1 postaje nula
    if(cvor != korijen && cvor -> roditelj -> lijevi != nullptr && cvor -> roditelj -> desni != nullptr)  //ako cvor ima brata
        cvor -> roditelj -> balans = 0;
    else
        azurirajBalans(cvor); 
    return cvor -> vrijednost;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::obrisi() {
    obrisiStablo(korijen);
    korijen = nullptr;
    broj_el = 0;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::obrisi(const TipK& kljuc) { 
    Cvor* del = trazi(korijen, kljuc);
    if(del == nullptr)
        throw "Kljuc ne postoji";
        
        if(del != korijen && del -> roditelj -> lijevi != nullptr && del -> roditelj -> desni != nullptr) {  //ako cvor ima brata
            if(del == del -> roditelj -> desni)
                del -> roditelj -> balans++;
            else 
                del -> roditelj -> balans--;
        }
        else
            azurirajBalans(del);
            
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
void AVLStabloMapa<TipK, TipV>::obrisiStablo(Cvor* cvor) {
    if(cvor == nullptr)
        return;
    obrisiStablo(cvor -> lijevi);
    obrisiStablo(cvor -> desni);
    delete cvor;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::kopirajStablo(Cvor*& cvor1, Cvor* cvor2, Cvor* roditelj1) {
    if(cvor2 == nullptr)
        return;
    cvor1 = new Cvor(cvor2 -> kljuc, cvor2 -> vrijednost, roditelj1, cvor2 -> balans);
    kopirajStablo(cvor1 -> lijevi, cvor2 -> lijevi, cvor1);
    kopirajStablo(cvor1 -> desni, cvor2 -> desni, cvor1);
    broj_el++;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::jednostrukaLijevaRotacija(Cvor* cvor) {
    //jednostruka lijeva rotacija 
    //da li je roditelj lijevo ili desno dijete svog roditelja?
    if(cvor -> roditelj -> roditelj != nullptr) {
        if(cvor -> roditelj == cvor -> roditelj -> roditelj -> lijevi)
            cvor -> roditelj -> roditelj -> lijevi = cvor;
        else
            cvor -> roditelj -> roditelj -> desni = cvor;
    }
    cvor -> roditelj -> desni = cvor -> lijevi; // roditelj preuzima lijevo podstablo
    if(cvor -> lijevi != nullptr)
        cvor -> lijevi -> roditelj = cvor -> roditelj;
    cvor -> lijevi = cvor -> roditelj;
    cvor -> roditelj = cvor -> roditelj -> roditelj;
    if(cvor -> roditelj == nullptr)
        korijen = cvor;
    cvor -> lijevi -> roditelj = cvor;
    cvor -> balans = 0;
    cvor -> lijevi -> balans = 0;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::jednostrukaDesnaRotacija(Cvor* cvor) {
    //jednostruka desna rotacija
    //da li je roditelj lijevo ili desno dijete svog roditelja?
    if(cvor -> roditelj -> roditelj != nullptr) {
        if(cvor -> roditelj == cvor -> roditelj -> roditelj -> lijevi)
            cvor -> roditelj -> roditelj -> lijevi = cvor;
        else
            cvor -> roditelj -> roditelj -> desni = cvor;
    }
    cvor -> roditelj -> lijevi = cvor -> desni; // roditelj preuzima lijevo podstablo
    if(cvor -> desni != nullptr)
        cvor -> desni -> roditelj = cvor -> roditelj;
    cvor -> desni = cvor -> roditelj;
    cvor -> roditelj = cvor -> roditelj -> roditelj;
    if(cvor -> roditelj == nullptr)
        korijen = cvor;
    cvor -> desni -> roditelj = cvor;
    cvor -> balans = 0;
    cvor -> desni -> balans = 0;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::azurirajBalans(Cvor* cvor) {
    if(cvor -> roditelj == nullptr)
        return;
    if(cvor == cvor -> roditelj -> lijevi)
        cvor -> roditelj -> balans++;
    else
        cvor -> roditelj -> balans--; 
    if(cvor -> roditelj -> balans < -1 || cvor -> roditelj -> balans > 1) {
        if(cvor -> roditelj -> balans < 0 && cvor -> balans < 0) {
            jednostrukaLijevaRotacija(cvor);
        }
        else if(cvor -> roditelj -> balans > 0 && cvor -> balans > 0) {
            jednostrukaDesnaRotacija(cvor);
        }
        else if(cvor -> roditelj -> balans > 0 && cvor -> balans < 0) {
            jednostrukaLijevaRotacija(cvor -> desni);
            jednostrukaDesnaRotacija(cvor -> roditelj);
        }
        else if(cvor -> roditelj -> balans < 0 && cvor -> balans > 0) {
            jednostrukaDesnaRotacija(cvor -> lijevi);
            jednostrukaLijevaRotacija(cvor -> roditelj);
        }
        else
            cvor -> roditelj -> balans--;
    }
    else
        azurirajBalans(cvor -> roditelj);
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::ispis() {
    ispisi(korijen);
    std::cout << std::endl;
}

template <typename TipK, typename TipV>
void AVLStabloMapa<TipK, TipV>::ispisi(Cvor* c) {
    if(c == nullptr) {
        return;
    }
    ispisi(c -> lijevi);
    if(c -> roditelj != nullptr)
        std::cout << "kljuc " << c -> kljuc << ", roditelj je -> " << c -> roditelj -> kljuc << ", balans: " << c -> balans << "\n";
    else 
        std::cout << "kljuc " << c -> kljuc << " <-- KORIJEN" << ", balans: " << c -> balans << "\n";
    ispisi(c -> desni);
}

#endif