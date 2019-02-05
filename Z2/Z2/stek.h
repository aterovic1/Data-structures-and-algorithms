#ifndef STEK_H
#define STEK_H

#define VEL 1000

template <typename Tip>
class Stek {
    Tip* S;
    int kapacitet;
    int vrh_steka;
    void povecaj_kapacitet();
public:
    Stek() : S(new Tip[VEL]), kapacitet(VEL), vrh_steka(-1) {}
    ~Stek() { delete[] S; }
    Stek(const Stek<Tip>& s);
    Stek<Tip>& operator =(const Stek<Tip>& s);
    void brisi() { vrh_steka = -1; }
    void stavi(const Tip&);
    const Tip skini();
    Tip& vrh() const;
    int brojElemenata() const { return vrh_steka + 1; }
};

template <typename Tip>
void Stek<Tip>::povecaj_kapacitet() {
    if(vrh_steka == kapacitet - 1) {
        kapacitet *= 2;
        Tip* S1 = new Tip[kapacitet];
        for(int i(0); i <= vrh_steka; i++)
            S1[i] = S[i];
        delete[] S;
        S = S1;
    }
}

template <typename Tip>
Stek<Tip>::Stek(const Stek<Tip>& s) : kapacitet(s.kapacitet), vrh_steka(s.vrh_steka) {
    S = new Tip[kapacitet];
    for(int i(0); i <= vrh_steka; i++)
        S[i] = s.S[i];
}

template <typename Tip>
Stek<Tip>& Stek<Tip>::operator =(const Stek<Tip>& s) {
    if(this == &s) return *this;
    delete[] S;
    kapacitet = s.kapacitet;
    vrh_steka = s.vrh_steka;
    S = new Tip[kapacitet];
    for(int i(0); i <= vrh_steka; i++)
        S[i] = s.S[i];
    return *this;
}

template <typename Tip>
void Stek<Tip>::stavi(const Tip& el) {
    povecaj_kapacitet();
    S[++vrh_steka] = el;
}

template <typename Tip>
const Tip Stek<Tip>::skini() {
    if(vrh_steka == -1) throw "GRESKA! Stek je prazan!";
    return S[vrh_steka--];
}

template <typename Tip>
Tip& Stek<Tip>::vrh() const {
    if(vrh_steka == -1) throw "GRESKA! Stek je prazan!";
    return S[vrh_steka];
}

#endif