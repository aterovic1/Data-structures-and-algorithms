#include "nizmapa.h"
#include "binstablomapa.h"
#include "hashmapa.h"

#include <iostream>

unsigned int hash(int ulaz, unsigned int max) {
	unsigned int suma = 23; 
	suma = suma + ulaz * 31;
	return suma % max;
}

int main() { 
    //NizMapa<int, int> m;
    //BinStabloMapa<int, int> m;
    HashMapa<int, int> m;
    m.definisiHashFunkciju(hash);
    
    int vel = 10000; //testiranje je vrseno sa 10 000 elemenata
    srand((unsigned)time(NULL));
    
    clock_t vrijeme1 = clock();
    //umetanje
    for(int i(0); i < vel; i++) {
        m[rand() % vel + 1] = 2 * i;
    }
    
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja (umetanje " << vel << " elemenata): " << ukvrijeme << " ms." << std::endl;
    //NizMapa -> 1600 ms, BinStabloMapa -> 42 ms, HashMapa -> 67 ms
    
    //umetanje u HashMapu i u BinStabloMapu je testirano jos jednom sa milion elemenata
    //rezultati su: BinStabloMapa -> 5500 ms, HashMapa -> 7900 ms
    
    vrijeme1 = clock();
    //pristup
    for(int i(0); i < vel; i++) {
        m.operator [](i);
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja (pristup " << vel << " elemenata): " << ukvrijeme << " ms." << std::endl;
    //NizMapa -> 2800 ms, BinStabloMapa -> 23 ms, HashMapa -> 44 ms
    
    vrijeme1 = clock();
    //brisanje
    for(int i(vel - 1); i >= 0; i--) {
        m.obrisi(i);
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja (brisanje " << vel << " elemenata): " << ukvrijeme << " ms." << std::endl;
    //NizMapa -> 1200 ms, BinStabloMapa -> 40 ms, HashMapa -> 7 ms
    
    return 0;
}