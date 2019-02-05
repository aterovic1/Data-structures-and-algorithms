#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>

using namespace std;

void radixSort(std::vector<int> &a) {
    std::vector<std::deque<int>> redovi(10);
    int k = 1;
    for(;;) {
        for(int broj : a) 
            redovi[(broj / k) % 10].push_back(broj);
        k *= 10;
        int i = 0;
        for(int j(0); j < redovi.size(); j++) {
            while(!redovi[j].empty()) {
                a[i++] = redovi[j].front();
                redovi[j].pop_front();
            }
            if(j == 0 && i == a.size()) 
                return;
        }
    }
}

bool je_li_list(int velicina, int i) {
    return(i < velicina && i >= velicina / 2);
}

void popravi_dolje(std::vector<int> &a, int i, int velicina) {
    while(!je_li_list(velicina, i)) {
        int veci = 2 * i + 1; // lijevo dijete
        int desno_d = 2 * i + 2;
        if(desno_d < velicina && a[desno_d] > a[veci])
            veci = desno_d;
        if(a[i] > a[veci])
            return;
        std::swap(a[i], a[veci]);
        i = veci;
    }
}

void stvoriGomilu(std::vector<int> &a) {
    int velicina = a.size();
    for(int i((velicina - 1) / 2); i >= 0; i--)
        popravi_dolje(a, i, velicina);
}

void popravi_gore(std::vector<int> &a, int i) {
    int roditelj = (i - 1) / 2;
    while(i > 0 && a[i] > a[roditelj]) {
        std::swap(a[i], a[roditelj]);
        i = roditelj;
        roditelj = (i - 1) / 2;
    }
}

void umetniUGomilu(std::vector<int> &a, int umetnuti, int &velicina) {
    a.push_back(umetnuti);
    velicina++;
    popravi_gore(a, velicina - 1);
}

int izbaciPrvi(std::vector<int> &a, int &velicina) {
    if(a.empty())
        throw "Gomila je prazna!\n";
    velicina--;
    std::swap(a[0], a[velicina]);
    if(velicina != 0)
        popravi_dolje(a, 0, velicina);
    return a[velicina];
}

void gomilaSort(std::vector<int> &a) {
    stvoriGomilu(a);
    int velicina = a.size();
    for(int i(0); i < a.size() - 1; i++)
        izbaciPrvi(a, velicina);
}

void gomila_sort(std::vector<int> &a) {
    stvoriGomilu(a);
    int velicina = a.size();
    for(int i(velicina - 1); i > 0; i--) {
        std::swap(a[i], a[0]);
        velicina--;
        popravi_dolje(a, 0, velicina);
    }
}

int main() {
    std::vector<int> a{6, 3, 2, 4, 24, 15, 17, 18, 12, 9};
    std::vector<int> b(a);
    radixSort(b);
    gomilaSort(a);
    bool OK = true;
    for(int i(0); i < a.size(); i++) 
        if(a[i] != b[i]) OK = false;
    std::cout << std::boolalpha << OK;
    return 0;
}  