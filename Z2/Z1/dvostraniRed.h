#ifndef DVOSTRANIRED_H
#define DVOSTRANIRED_H

template <typename Tip>
class DvostraniRed {
    struct Cvor {
        Tip element;
        Cvor* sljedeci;
        Cvor* prethodni;
        Cvor(const Tip& el) : element(el), sljedeci(nullptr), prethodni(nullptr) {}
    };
    int broj_el;
    Cvor* pocetak;
    Cvor* kraj;
public:
    DvostraniRed() : broj_el(0), pocetak(nullptr), kraj(nullptr) {}
    ~DvostraniRed();
    DvostraniRed(const DvostraniRed<Tip>& dRed);
    DvostraniRed<Tip>& operator =(const DvostraniRed<Tip>& dRed);
    int brojElemenata() const { return broj_el; }
    void brisi();
    void staviNaVrh(const Tip&);
    Tip skiniSaVrha();
    void staviNaCelo(const Tip&);
    Tip skiniSaCela();
    Tip& vrh() const;
    Tip& celo() const;
};

template <typename Tip>
DvostraniRed<Tip>::~DvostraniRed() {
    while(kraj != nullptr) {
        Cvor* tmp = kraj;
        kraj = kraj -> prethodni;
        delete tmp;
    }
}

template <typename Tip>
DvostraniRed<Tip>::DvostraniRed(const DvostraniRed<Tip>& dRed) : broj_el(dRed.broj_el) {
    Cvor* tmp = dRed.pocetak;
    Cvor* tmp1 = nullptr;
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp1 == nullptr)
            pocetak = novi;
        else {
            novi -> prethodni = tmp1;
            tmp1 -> sljedeci = novi;
        }
        tmp1 = novi;
        tmp = tmp -> sljedeci;
    }
    kraj = tmp1;
}

template <typename Tip>
DvostraniRed<Tip>& DvostraniRed<Tip>::operator =(const DvostraniRed<Tip>& dRed) {
    if(this == &dRed) return *this;
    while(kraj != nullptr) {
        Cvor* tmp = kraj;
        kraj = kraj -> prethodni;
        delete tmp;
    }
    broj_el = dRed.broj_el;
    Cvor* tmp = dRed.pocetak;
    Cvor* tmp1 = nullptr;
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp1 == nullptr)
            pocetak = novi;
        else {
            novi -> prethodni = tmp1;
            tmp1 -> sljedeci = novi;
        }
        tmp1 = novi;
        tmp = tmp -> sljedeci;
    }
    kraj = tmp1;
    return *this;
}

template <typename Tip>
void DvostraniRed<Tip>::brisi() {
    while(pocetak != nullptr) {
        Cvor* tmp = pocetak;
        pocetak = pocetak -> sljedeci;
        delete tmp;
    }
    broj_el = 0;
}

template <typename Tip>
void DvostraniRed<Tip>::staviNaVrh(const Tip& el) {
    Cvor* novi = new Cvor(el);
    if(broj_el == 0)
        pocetak = novi;
    else {
        novi -> prethodni = kraj;
        kraj -> sljedeci = novi;
    }
    kraj = novi;
    broj_el++;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaVrha() {
    if(broj_el == 0) throw "GRESKA! Nista za izbaciti!";
    Cvor* tmp = kraj;
    Tip ret = tmp -> element;
    kraj = kraj -> prethodni;
    if(kraj != nullptr)
        kraj -> sljedeci = nullptr;
    if(tmp == pocetak)
        pocetak = nullptr;
    delete tmp;
    broj_el--;
    return ret;
}

template <typename Tip>
void DvostraniRed<Tip>::staviNaCelo(const Tip& el) {
    Cvor* novi = new Cvor(el);
    if(broj_el == 0)
        kraj = novi;
    else {
        novi -> sljedeci = pocetak;
        pocetak -> prethodni = novi;
    }
    pocetak = novi;
    broj_el++;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaCela() {
    if(broj_el == 0) throw "GRESKA! Nista za izbaciti!";
    Cvor* tmp = pocetak;
    Tip ret = tmp -> element;
    pocetak = pocetak -> sljedeci;
    if(pocetak != nullptr)
        pocetak -> prethodni = nullptr;
    if(tmp == kraj)
        kraj = nullptr;
    delete tmp;
    broj_el--;
    return ret;
}

template <typename Tip>
Tip& DvostraniRed<Tip>::vrh() const {
    if(broj_el == 0) throw "GRESKA! Prazan red!";
    return kraj -> element;
}

template <typename Tip>
Tip& DvostraniRed<Tip>::celo() const {
    if(broj_el == 0) throw "GRESKA! Prazan red!";
    return pocetak -> element;
}

#endif
