#include "nizmapa.h"
#include <iostream>

int main() {
    try {
        NizMapa<int, int> kvadrati;
        for(int i(0); i < 600; i++)
            kvadrati[i] = i * i;
        std::cout << kvadrati.brojElemenata() << "\n";
        kvadrati.obrisi(15);
        std::cout << kvadrati.brojElemenata() << std::endl;
        kvadrati[16] = 16;
        for(int i(10); i < 20; i++ )
            std::cout << kvadrati[i] << " ";
        std::cout << std::endl;
        
        NizMapa<int, bool> stepen_dvojke;
        for(int i(1); i < 1000; i++)
            stepen_dvojke[i] = (i & (i - 1)) == 0;
        if(stepen_dvojke[64] && stepen_dvojke[32])
            std::cout << "OK\n";
        std::cout << std::boolalpha << stepen_dvojke[50] << std::endl;
        
        NizMapa<int, int> kubovi(kvadrati);
        for(int i(0); i < kubovi.brojElemenata(); i++)
            kubovi[i] = i * i * i;
        std::cout << kvadrati[5] << " " << kubovi[5] << "\n";
        
        kvadrati.obrisi();
        std::cout << kvadrati.brojElemenata() << std::endl;
        
        kvadrati = kubovi;
        std::cout << kvadrati[15] << " " << kvadrati.brojElemenata() << "\n";
        kvadrati.obrisi(6000); // izuzetak
    }
    catch(const char error[]) {
        std::cout << error;
    }
    return 0;
}