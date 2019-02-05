#ifndef MAPA_H
#define MAPA_H

template <typename TipK, typename TipV>
class Mapa {
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual TipV operator [](const TipK& kljuc) const = 0;
    virtual TipV& operator [](const TipK& kljuc) = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipK& kljuc) = 0;
};

#endif