#ifndef GNORIENTATO_H
#define GNORIENTATO_H
#include "grafo.h"

class gNOrientato :public grafo
{
public:
    ~gNOrientato();
    gNOrientato();
    gNOrientato(int);//costruttore per creare 0 o più nodi nella stessa invocazione
    gNOrientato(const gNOrientato&);
    virtual void AggiungiA(const nodo &,const nodo &);
    virtual bool EliminaA(const nodo &,const nodo &);
    virtual int TaglioMin()const;
    virtual bool Albero()const;
    virtual int RicercaTaglioMin(int t)const;
    virtual std::vector<grafo *> ComponentiConnesse()const;
    virtual gNOrientato *ComponenteConnessa(const nodo &, std::vector<nodo> &) const;
    virtual gNOrientato *ComplementoGrafo()const;
    virtual int NArchi()const;
    bool planare()const;
    bool k5(std::vector<grafo::nodo>& , const grafo::nodo & );
    std::vector<int> bipartito()const;
    bool bipartito(const grafo::nodo&,std::vector<grafo::nodo>&, std::vector<grafo::nodo>&, bool =false)const;
    bool bipartitoCompletoK33(std::vector<grafo::nodo>&);
    bool k33();
    unsigned int Grado(const grafo::nodo & n)const;

};


#endif // GNORIENTATO_H
