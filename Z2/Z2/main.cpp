#include "stek.h"
#include <iostream>
#include <vector>

using namespace std;

int pretraziBinarno(std::vector<int> v, int t) {
    if(v.empty()) 
        return -1;
    int pocetak = 0;
    int kraj = v.size() - 1;
    while(kraj > pocetak) {
        int srednji = (pocetak + kraj) / 2;
        if(v[srednji] < t)
            pocetak = srednji + 1;
        else
            kraj = srednji;
    }
    if(v[kraj] == t)
        return kraj;
    return -1;
}

void pretraga(Stek<std::vector<int>>& s, int trazeni) {
    if(s.brojElemenata() == 0) {
        std::cout << "Nema elementa";
        return;
    }
    if(!s.vrh().empty() && s.vrh()[0] <= trazeni) {
        int t = pretraziBinarno(s.vrh(), trazeni);
        t != -1 ? std::cout << t << " " << s.brojElemenata() - 1 : std::cout << "Nema elementa";
        return;
    }
    else {
        std::vector<int> v = s.skini();
        pretraga(s, trazeni);
        s.stavi(v);
    }
}

int main() {
    Stek<std::vector<int>> s;
    s.stavi({4,5});
    s.stavi({6,8});
    s.stavi({9,10,130});
    s.stavi({});
    s.stavi({157,226});
    s.stavi({230,240,297,300,301});
    s.stavi({344,587,691});
    s.stavi({777,1000,1007,1111,1222,1478,1479,1497});
    pretraga(s, 777);
    //Provjeravamo da li je stek ostao nepromijenjen
    std::cout << "\n\n";
    while(s.brojElemenata()) {
        for(int x : s.vrh())
            std::cout << x << " ";
        std::cout << std::endl;
        s.skini();
    }
    return 0;
}