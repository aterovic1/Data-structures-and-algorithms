#include "dvostraniRed.h"
#include <iostream>

void testiraj() {
    DvostraniRed<int> l;
    clock_t vrijeme1 = clock();
    for(int i(0); i < 1000000; i++)
        l.staviNaCelo(i);
    for(int i(0); i < 1000000; i++)
        l.skiniSaVrha(); 
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}

int main() {
    DvostraniRed<int> d;
    d.staviNaCelo(3);
    d.staviNaVrh(6);
    d.staviNaCelo(2);
    d.staviNaVrh(4);
    d.staviNaCelo(7);
    std::cout << d.brojElemenata() << std::endl;
    DvostraniRed<int> r(d);
    r.celo() = 10;
    d.vrh() = 10;
    while(r.brojElemenata())
        std::cout << r.skiniSaCela() << " ";
    std::cout << std::endl << r.brojElemenata() << std::endl;
    while(d.brojElemenata())
        std::cout << d.skiniSaVrha() << " ";
    std::cout << std::endl << d.brojElemenata() << std::endl;
    d = r;
    r.staviNaCelo(1);
    r.staviNaCelo(2);
    d.staviNaVrh(1);
    d.brisi();
    if(r.brojElemenata() == d.brojElemenata() + 2 && r.celo() != 1) 
        std::cout << "OK" << std::endl;
    std::cout << "Test ubacivanja i izbacivanja milion elemenata: ";
    testiraj();
    return 0;
}