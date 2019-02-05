#include "stek.h"
#include <iostream>
#include <ctime>

int main() {
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
    std::cout << " vrh je sada " << s.vrh() << std::endl;
    std::cout << "Stavljanje i skidanje 10 miliona elemenata: ";
    _main();
    return 0;
}

int _main() {
    Stek<int> s;

    clock_t vrijeme1 = clock();
    for(int i(0); i < 10000000; i++)
        s.stavi(i);
    for(int i(0); i < 10000000; i++)
        s.skini();
    clock_t vrijeme2 = clock();
    
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    return 0;
}