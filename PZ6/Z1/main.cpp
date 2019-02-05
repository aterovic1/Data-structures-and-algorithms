#include <iostream>
#include <string>
#include <fstream>

template <typename Tip>
void insertionsort(Tip* niz, int vel) {
    for(int i(1); i < vel; i++) {
        Tip priv = niz[i];
        int j(i - 1);
        for(; j >= 0 && niz[j] > priv; j--)
            niz[j + 1] = niz[j];
        niz[j + 1] = priv;
    }
}

template <typename Tip>
void shellsort(Tip* niz, int vel) {
    for(int h(vel / 2); h > 0; h /= 2) {
        for(int i(h); i < vel; i++) {
            Tip priv = niz[i];
            int j(i - h);
            for(; j >= 0 && niz[j] > priv; j -= h) 
                niz[j + h] = niz[j];
            niz[j + h] = priv;
        }
    }
}

template <typename Tip>
void merge(Tip* niz, int l, int p, int q, int u) {
    int i = 0, j = q - l, k = l;
    Tip* pomniz = new Tip[u - l + 1];
    for(int m(0); m <= u - l; m++)
        pomniz[m] = niz[l + m];
    while(i <= p - l && j <= u - l) {
        if(pomniz[i] < pomniz[j])
            niz[k] = pomniz[i++];
        else
            niz[k] = pomniz[j++];
        k++;
    }
    while(i <= p - l)
        niz[k++] = pomniz[i++];
    while(j <= u - l)
        niz[k++] = pomniz[j++];
    delete[] pomniz;
}

template <typename Tip>
void mergesort(Tip* niz, int l, int u) {
    if(u > l) {
        int p = (u + l -1) / 2;
        int q = p + 1;
        mergesort(niz, l, p);
        mergesort(niz, q, u);
        merge(niz, l, p, q, u);
    }
}

template <typename Tip>
int particija(Tip* niz, int poc, int kr) {
    Tip pivot = niz[poc];
    int p = poc + 1;
    while(p <= kr && niz[p] < pivot)
        p++;
    for(int i(p + 1); i <= kr; i++) {
        if(niz[i] < pivot) {
            std::swap(niz[i], niz[p]);
            p++;
        }
    }
    std::swap(niz[poc], niz[p - 1]);
    return p - 1;
}

template <typename Tip>
void quicksort(Tip* niz, int poc, int kr) {
    if(poc < kr) {
        int j = particija(niz, poc, kr);
        quicksort(niz, poc, j - 1);
        quicksort(niz, j + 1, kr);
    }
}

template <typename Tip> 
void bubble_sort(Tip* niz, int vel) {
    for(int i(vel - 1); i > 0; i--) {
        for(int j(1); j <= i; j++) {
            if(niz[j] < niz[j - 1])
                std::swap(niz[j], niz[j - 1]);
        }
    }
}

template <typename Tip>
void modif_bubble_sort(Tip* niz, int vel) {
    int p = vel;
    for(int i(p - 1); i > 0; i--) {
        p = 0;
        for(int j(0); j < i; j++) {
            if(niz[j] > niz[j + 1]) {
                std::swap(niz[j], niz[j + 1]);
                p = j;
            }
        }
        if(p == 0) return;
    }
}

template <typename Tip> 
void selection_sort(Tip* niz, int vel) {
    for(int i(0); i < vel - 1; i++) {
        int min = i;
        for(int j(i + 1); j < vel; j++) {
            if(niz[j] < niz[min]) 
                min = j;
        }
        std::swap(niz[i], niz[min]);
    }
}

template <typename Tip> 
void quick_sort(Tip* niz, int vel) {
    quicksort(niz, 0, vel - 1);
}

template <typename Tip> 
void merge_sort(Tip* niz, int vel) {
    mergesort(niz, 0, vel - 1);
}

void povecaj_kapacitet(int*& niz, int& max_vel) {
    int* novi_niz = new int[max_vel * 2];
    for(int i(0); i < max_vel; i++)
        novi_niz[i] = niz[i];
    delete[] niz;
    niz = novi_niz;
    novi_niz = nullptr;
    max_vel *= 2;
}

void ucitaj(std::string filename, int*& niz, int& vel) {
    std::ifstream ulaz(filename);
    int max_vel = 50000;
    niz = new int[max_vel];
    int broj, i = 0;
    while(ulaz >> broj) {
        if(i == max_vel)
            povecaj_kapacitet(niz, max_vel);
        niz[i++] = broj;
    }
    vel = i;
}

void generisi(std::string filename, int vel) {
    std::ofstream izlaz(filename);
    srand((unsigned)time(NULL));
    for(int i(0); i < vel; i++) 
        izlaz << rand() % 100000 + 1 << std::endl;
}

bool da_li_je_sortiran(int* niz, int vel) {
    for(int i(1); i < vel; i++)
        if(niz[i] < niz[i - 1])
            return false;
    return true;
}

void upisi_u_dat(std::string filename, int* niz, int vel) {
    std::string sort_dat = filename.substr(0, filename.length() - 4) + "_sortirano.txt";
    std::ofstream izlaz(sort_dat);
    for(int i(0); i < vel; i++) 
        izlaz << niz[i] << std::endl;
    std::cout << "Sortiran niz je upisan u datoteku: '" << sort_dat << "'.\n";
}

int main() {
    std::string filename;
    std::cout << "Unesite ime ili put datoteke: ";
    std::getline(std::cin, filename);
    generisi(filename, 10000);
    int* niz, n, vel = 0;
    ucitaj(filename, niz, vel);
    
    std::cout << "▼  Odaberite algoritam sortiranja: \n";
    std::cout << "1. Bubble sort\n";
    std::cout << "2. Selection sort\n";
    std::cout << "3. Quick sort\n";
    std::cout << "4. Merge sort\n";
    std::cin >> n;
    
    std::cout << "Sortiranje " << vel << " elemenata koristeci";
    clock_t vrijeme1 = clock();
    if(n == 1) {
        std::cout << " bubble sort: ";
        bubble_sort(niz, vel);
    }
    else if(n == 2) {
        std::cout << " selection sort: ";
        selection_sort(niz, vel);
    }
    else if(n == 3) {
        std::cout << " quick sort: ";
        quick_sort(niz, vel);
    }
    else {
        std::cout << " merge sort: ";
        merge_sort(niz, vel);
    }
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
    std::cout << "vrijeme izvrsenja " << ukvrijeme << " ms.\n";
    
    da_li_je_sortiran(niz, vel) ? std::cout << "Niz je uspjesno sortiran!\n" : "Niz nije uspjesno sortiran!\n";
    upisi_u_dat(filename, niz, vel);
    
    delete[] niz;
    return 0;
}