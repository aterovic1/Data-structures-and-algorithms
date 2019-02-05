#include <iostream>

int fib(int n) {
    if(n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

int fib2_0(int n, int a = 0, int b = 1) {
    if(n < 1) return a;
    return fib2_0(n - 1, b, a + b);
}

/* DRUGI NACIN (fib2_0 sa jednim parametrom)
int pom(int n, int a = 0, int b = 1) {
    if(n < 1) return a;
    return pom(n - 1, b, a + b);
}
int fib2_0(int n) {
    return pom(n, 0, 1);
}*/

int fib_petlja (int n) {
    if (n<=1) return n;
    int pretprosli(0), prosli(1), rezultat;
    for (int i(2); i<=n; i++) {
        rezultat = pretprosli+prosli;
        pretprosli = prosli;
        prosli = rezultat;
    }
    return rezultat;
}

int nzd(int x, int y) {
    if(y == 0) return x;
    return nzd(y, x % y);
}

void testiraj(int f, int n) {
    std::cout << f << ". Fibonaccijev broj";
    clock_t vrijeme1 = clock();
    if(n == 1)
        std::cout << ", koristeci eksponencijalnu rekurziju, je " << fib(f);
    else if(n == 2)
        std::cout << ", koristeci repnu rekurziju, je " << fib2_0(f);
    else
        std::cout << ", koristeci iterativni postupak, je " << fib_petlja(f);
    std::cout << ".\n";
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms.\n" << std::endl;
}

int main() {
    int m, n;
    for(;;) {
        std::cout << "Izaberite opciju:\n";
        std::cout << "1. Ispis n-tog Fibonaccijevog broja (eksponencijalna rekurzija)\n";
        std::cout << "2. Ispis n-tog Fibonaccijevog broja (repna rekurzija)\n";
        std::cout << "3. Ispis n-tog Fibonaccijevog broja (iterativni postupak)\n";
        std::cout << "4. Racunanje najveceg zajednickog djelioca\n";
        std::cout << "0. Izlaz\n";
        std::cout << "-----------------\n\n";
        std::cin >> m;
        switch(m) {
            case 1:
                std::cout << "Unesite n: ";
                std::cin >> n;
                testiraj(n, 1);
                break;
            case 2:
                std::cout << "Unesite n: ";
                std::cin >> n;
                testiraj(n, 2);
                break;
            case 3:
                std::cout << "Unesite n: ";
                std::cin >> n;
                testiraj(n, 3);
                break;
            case 4:
                int a, b;
                std::cout << "Unesite 2 broja: ";
                std::cin >> a >> b;
                std::cout << "Njihov najveci zajednicki djelilac je " << nzd(a, b) << ".\n\n";
                break;
            case 0:
                return 0;
            default:
                std::cout << "Pogresna komanda!";
                return 0;
        }
    }
}