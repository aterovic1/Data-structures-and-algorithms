#include "nizmapa.h"
#include "binstablomapa.h"

#include <iostream>
#include <string>

int _main() {
    Mapa<int, int>* m;
    m = new BinStabloMapa<int, int>;
    
    srand((unsigned)time(NULL));
    int vel(100000); //nmapa je testirana sa puno manjim brojem elemenata zbog vremena izvrsavanja, vec ovdje vidimo da je bsmapa puno brza od nmape
    for(int i(0); i < vel; i++) {
        (*m)[rand() % vel + 1] = i;
    }
    for(int i(0); i < 10000; i++) {
        (*m)[i] = 2 * i;
    }
    
    clock_t vrijeme1 = clock();
    //dodavanje novog elementa u bsmapu, prosjecno 0.9 ms
    //za nmapu, prosjecno 1.7 ms
    (*m)[rand() % vel + vel + 1] = 25; 
    clock_t vrijeme2 = clock();
    
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "Vrijeme izvrsenja (dodavanje): " << ukvrijeme << " mikro sec." << std::endl;
    
    vrijeme1 = clock();
    //pristup postojecem elementu u bsmapi, prosjecno 0.6 ms
    //za nmapu, prosjecno 1.1 ms
    (*m)[rand() % 10000];
    vrijeme2 = clock();
    
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "Vrijeme izvrsenja (pristup elementu): " << ukvrijeme << " mikro sec." << std::endl;
    delete m;
    return 0;
}

int __main() { try {
    //NizMapa<int, int> m;
    BinStabloMapa<int, int> m;
    //HashMapa<int, int> m;
    //m.definisiHashFunkciju(hash);
    int vel = 500000;
    
    clock_t vrijeme1 = clock();
    //umetanje
    for(int i(0); i < vel; i++) {
        m[i] = 2 + i;
    }
    //m.ispis();
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja (umetanje " << vel << " elemenata): " << ukvrijeme << " ns." << std::endl;
    //NizMapa -> 4s, BinStabloMapa ->  , HashMapa -> 
    
    vrijeme1 = clock();
    //pristup
    for(int i(0); i < vel; i++) {
        m.operator [](i);
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja (pristup " << vel << " elemenata): " << ukvrijeme << " ns." << std::endl;
    //NizMapa -> 4s, BinStabloMapa ->  , HashMapa -> 
    
    vrijeme1 = clock();
    //brisanje
    for(int i(0); i < vel; i += 10) {
        m.obrisi(i);
    }
    vrijeme2 = clock();
    ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja (brisanje " << vel / 10 << " elemenata): " << ukvrijeme << " ns." << std::endl;
    //NizMapa -> 4s, BinStabloMapa ->  , HashMapa -> 
}
    catch(const char err[]) {
        std::cout << err;
    }
    return 0;
}


int main() {
    BinStabloMapa <int, int> b;
    b[3] = 3;
    b[2] = 2;
    b[6] = 6;
    b[1] = 1;
    b[4] = 4;
    b[5] = 5;
    b[7] = 7;
    b.ispis();
    
    std::vector<int> a(b.od_do(3, 9));
    for(int x : a)
        std::cout << x << " ";
    
    return 0;
}