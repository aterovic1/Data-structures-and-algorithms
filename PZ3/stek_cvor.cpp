#include <iostream>

template <typename Tip>
class Stek {
    struct Cvor {
        Tip element;
        Cvor* prethodni;
        Cvor(const Tip& el) : element(el), prethodni(nullptr) {}
    };
    int broj_el;
    Cvor* top;
public:
    Stek() : broj_el(0), top(nullptr) {}
    ~Stek();
    Stek(const Stek<Tip>& s);
    Stek<Tip>& operator =(const Stek<Tip>& s);
    void brisi();
    void stavi(const Tip&);
    Tip skini();
    Tip& vrh() const;
    int brojElemenata() const { return broj_el; }
};

template <typename Tip>
Stek<Tip>::Stek(const Stek<Tip>& s) : broj_el(s.broj_el) {
    Cvor* tmp = s.top, *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp == s.top) 
            top = tmp1 = novi;
        else
            tmp1 -> prethodni = novi;
        tmp1 = novi;
        tmp = tmp -> prethodni;
    }
}

template <typename Tip>
Stek<Tip>::~Stek() {
    while(top != nullptr) {
        Cvor* tmp(top);
        top = top -> prethodni;
        delete tmp;
    }
}

template <typename Tip>
Stek<Tip>& Stek<Tip>::operator =(const Stek<Tip>& s) {
    if(this == &s) return *this;
    broj_el = s.broj_el;
    while(top != nullptr) {
        Cvor* tmp(top);
        top = top -> prethodni;
        delete tmp;
    }
    Cvor* tmp = s.top, *tmp1(nullptr);
    while(tmp != nullptr) {
        Cvor* novi = new Cvor(tmp -> element);
        if(tmp == s.top) 
            top = novi;
        else
            tmp1 -> prethodni = novi;
        tmp1 = novi;
        tmp = tmp -> prethodni;
    }
    return *this;
}

template <typename Tip>
void Stek<Tip>::stavi(const Tip& el) {
    Cvor* novi = new Cvor(el);
    novi -> prethodni = top;
    top = novi;
    broj_el++;
}

template <typename Tip>
Tip Stek<Tip>::skini() {
    if(broj_el == 0) throw "GRESKA! Stek je prazan!";
    Tip ret = top -> element;
    Cvor* tmp = top;
    top = top -> prethodni;
    delete tmp;
    broj_el--;
    return ret;
}

template <typename Tip>
Tip& Stek<Tip>::vrh() const {
    if(broj_el == 0) throw "GRESKA! Stek je prazan!";
    return top -> element;
}

template <typename Tip>
void Stek<Tip>::brisi() {
    while(top != nullptr) {
        Cvor* tmp(top);
        top = top -> prethodni;
        delete tmp;
    }
    broj_el = 0;
}

int _main() {
    Stek<int> s;
    for(int i(0); i < 1200; i++) s.stavi(i);
    std::cout << s.brojElemenata() << std::endl;
    for(int i(0); i < 5; i++) { std::cout << s.skini() << " "; }
    Stek<int> s1(s);
    s1.brisi(); 
    s1.stavi(17); 
    s1.stavi(20);
    s = s1; std::cout << "**" << s.brojElemenata() << "**";
    for(int i(0); i < 1; i++) std::cout << s.skini() << " ";
    std::cout << " -> " << s.vrh() << " <-   ";
    std::cout << s.brojElemenata();
    s.vrh() = 5;
    std::cout << " vrh je sada " << s.vrh();
    s.skini();
    s1 = s;
    std::cout << " " << s1.brojElemenata();
    return 0;
}

int main() {
    Stek<int> s;
    
    clock_t vrijeme1 = clock();
    for(int i(0); i < 1000000; i++)
        s.stavi(i);
    for(int i(0); i < 1000000; i++)
        s.skini();
    clock_t vrijeme2 = clock();
    
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    return 0;
}