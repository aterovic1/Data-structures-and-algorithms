#include "dplista.h"
#include "iterator.h"
#include <iostream>

void testiraj() {
    DvostrukaLista<int> l;
    clock_t vrijeme1 = clock();
    for(int i(0); i < 1000000; i++)
        l.dodajIspred(i);
    for(int i(0); i < 1000000; i++)
        l.obrisi();
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}

int main() {
    DvostrukaLista<int> l;
    l.dodajIspred(10);
    l.dodajIspred(5);
    std::cout << l.trenutni();
    std::cout << std::endl;
    l.dodajIza(8);
    l.dodajIza(9);
    std::cout << l.trenutni();
    std::cout << std::endl;
    l.sljedeci(); l.sljedeci();
    std::cout << l.trenutni();
    std::cout << std::endl;
    l.prethodni(); l.prethodni(); l.prethodni();
    std::cout << l.trenutni();
    std::cout << std::endl;
    l.obrisi(); l.obrisi();
    std::cout << l.trenutni();
    std::cout << std::endl;
    l.sljedeci(); l.obrisi();
    std::cout << l.trenutni();
    std::cout << std::endl;
    std::cout << l.brojElemenata();
    std::cout << std::endl;
    l.trenutni() = 12;
    l.dodajIspred(11);
    l.dodajIza(13);
    std::cout << l[2];
    std::cout << std::endl;
    l[0] = 10;
    
    std::cout << std::endl;
    DvostrukaLista<int> d(l);
    d.pocetak();
    d.obrisi();
    d[0] = 5;
    std::cout << d.brojElemenata();
    std::cout << std::endl;
    d.kraj();
    std::cout << std::boolalpha << d.sljedeci();
    std::cout << std::endl;
    
    std::cout << std::endl;
    l = d;
    std::cout << l.trenutni();
    std::cout << std::endl;
    l.obrisi();
    std::cout << l.trenutni();
    std::cout << std::endl;
    std::cout << l.brojElemenata();
    std::cout << std::endl;
    l.obrisi();
    
    DvostrukaLista<int> s;
    s.dodajIspred(7);
    s.dodajIspred(14);
    s.dodajIspred(6);
    s.dodajIspred(4);
    s.dodajIspred(14);
    s.dodajIspred(5);
    std::cout << "Max je: " << dajMaksimum(s) << std::endl;
    
    std::cout << "Test za milion ubacivanja i izbacivanja: ";
    testiraj();
    return 0;
}