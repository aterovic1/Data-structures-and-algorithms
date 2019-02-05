#include "nizlistatmp.h"
#include "jplistatmp.h"
#include <iostream>

int Menu() {
    int izbor;
    std::cout << std::endl << "---Menu-----------------------------\n\n";
    std::cout << "1. Idi na prethodni\n";
    std::cout << "2. Idi na sljedeci\n";
    std::cout << "3. Umetanje ispred tekuceg elementa\n";
    std::cout << "4. Umetanje iza tekuceg elementa\n";
    std::cout << "5. Idi na pocetak\n";
    std::cout << "6. Idi na kraj\n";
    std::cout << "7. Daj vrijednost tekuceg elementa\n";
    std::cout << "8. Obrisi tekuci element\n";
    std::cout << "9. Izmijeni tekuci element\n";
    std::cout << "10. Broj elemenata u listi\n";
    std::cout << "0. Izlaz\n\n";
    std::cout << std::endl << "-----------------Izaberite opciju: ";
    std::cin >> izbor;
    if(std::cin) return izbor;
    else {
        std::cin.clear();
        std::cin.ignore(9999, '\n');
        return -1;
    }
}

int main() {
    Lista<int>* l;
    int n;
    ponovo: std::cout << "Sta zelite koristiti? Unesite 1 za 'NizLista' ili 2 za 'JednostrukaLista': ";
    std::cin >> n;
    if(n == 1) l = new NizLista<int>;
    else if(n == 2) l = new JednostrukaLista<int>;
    else goto ponovo;
    int izbor, x;
    while(izbor = Menu()) {
        try {
            switch(izbor) {
                case 0:
                    delete l;
                    return 0;
                case 1:
                    l -> prethodni();
                    break;
                case 2:
                    l -> sljedeci();
                    break;
                case 3:
                    std::cout << "Unesite broj koji zelite dodati: ";
                    std::cin >> x;
                    l -> dodajIspred(x);
                    break;
                case 4: 
                    std::cout << "Unesite broj koji zelite dodati: ";
                    std::cin >> x;
                    l -> dodajIza(x);
                    break;
                case 5:
                    l -> pocetak();
                    break;
                case 6: 
                    l -> kraj();
                    break;
                case 7:
                    std::cout << "Vrijednot tekuceg elementa je: " << l -> trenutni();
                    break;
                case 8:
                    l -> obrisi();
                    break;
                case 9:
                    std::cout << "Unesite novu vrijednost: ";
                    std::cin >> x;
                    l -> trenutni() = x;
                    break;
                case 10:
                    std::cout << "Broj elemenata u listi je: " << l -> BrojElemenata() << std::endl;
                    break;
                default:
                    std::cout << "Pogresan izbor!";
            }
        }
        catch(const char poruka[]) {
            std::cout << poruka;
        }
    }
    return 0;
}