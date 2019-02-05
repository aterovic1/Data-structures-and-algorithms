#ifndef RED_H
#define RED_H

template <typename Tip>
class Red {
    struct Cvor {
        Tip element;
        Cvor* sljedeci;
        Cvor(const Tip& el) : element(el), sljedeci(nullptr) {}
    };
    int broj_el;
    Cvor* pocetak, *kraj;
public:
    Red() : broj_el(0), pocetak(nullptr), kraj(nullptr) {}
    ~Red();
    Red(const Red<Tip>& red);
    Red<Tip>& operator =(const Red<Tip>& red);
    void brisi();
    void stavi(const Tip&);
    Tip skini();
    Tip& celo() const;
    int brojElemenata() const { return broj_el; }
};

template <typename Tip>
Red<Tip>::~Red() {
    while(pocetak != nullptr) {
        Cvor* tmp = pocetak;
        pocetak = pocetak -> sljedeci;
        delete tmp;
    }
}

template <typename Tip>
Red<Tip>::Red(const Red<Tip>& red) : broj_el(red.broj_el) {
    Cvor* tmp(red.pocetak), *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp1 == nullptr)
            pocetak = novi;
        else
            tmp1 -> sljedeci = novi;
        tmp1 = novi;
        tmp = tmp -> sljedeci;
    }
    kraj = tmp1;
}

template <typename Tip>
Red<Tip>& Red<Tip>::operator =(const Red<Tip>& red) {
    if(this == &red) return *this;
    broj_el = red.broj_el;
    while(pocetak != nullptr) {
        Cvor* tmp = pocetak;
        pocetak = pocetak -> sljedeci;
        delete tmp;
    }
    Cvor* tmp(red.pocetak), *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp1 == nullptr)
            pocetak = novi;
        else
            tmp1 -> sljedeci = novi;
        tmp1 = novi;
        tmp = tmp -> sljedeci;
    }
    return *this;
}

template <typename Tip>
void Red<Tip>::brisi() {
    while(pocetak != nullptr) {
        Cvor* tmp = pocetak;
        pocetak = pocetak -> sljedeci;
        delete tmp;
    }
    broj_el = 0;
}

template <typename Tip>
void Red<Tip>::stavi(const Tip& el) {
    Cvor *novi = new Cvor(el);
    if(broj_el == 0)
        pocetak = novi;
    else 
        kraj -> sljedeci = novi;
    kraj = novi;
    broj_el++;
}

template <typename Tip>
Tip Red<Tip>::skini() {
    if(broj_el == 0) throw "GRESKA! Red je prazan!";
    Tip ret = pocetak -> element;
    Cvor* tmp = pocetak;
    pocetak = pocetak -> sljedeci;
    delete tmp;
    if(broj_el == 1)
        kraj = nullptr;
    broj_el--;
    return ret;
}

template <typename Tip>
Tip& Red<Tip>::celo() const {
    if(broj_el == 0) throw "GRESKA! Red je prazan!";
    return pocetak -> element;
}

#endif