#include "red.h"
#include <iostream>

void testiraj() {
    Red<int> s;
    clock_t vrijeme1 = clock();
    for(int i(0); i < 1000000; i++)
        s.stavi(i);
    for(int i(0); i < 1000000; i++)
        s.skini();
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
}

int main() {
    Red<int> s;
    for(int i(0); i < 1200; i++) s.stavi(i);
    std::cout << s.brojElemenata() << std::endl;
    for(int i(0); i < 5; i++) { std::cout << s.skini() << " "; }
    Red<int> s1(s);
    s1.brisi(); 
    s1.stavi(17); 
    s1.stavi(20);
    s = s1; std::cout << "**" << s.brojElemenata() << "**";
    for(int i(0); i < 1; i++) std::cout << s.skini() << " ";
    std::cout << " -> " << s.celo() << " <-   ";
    std::cout << s.brojElemenata();
    s.celo() = 5;
    std::cout << " vrh je sada " << s.celo();
    s.skini();
    s1 = s;
    std::cout << " " << s1.brojElemenata() << std::endl;
    std::cout << "Stavljanje i skidanje milion elemenata: ";
    testiraj();
    return 0;
}
