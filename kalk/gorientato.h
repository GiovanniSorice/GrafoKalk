#ifndef GORIENTATO_H
#define GORIENTATO_H
#include "grafo.h"

class gOrientato :public grafo
{
    friend std::ostream& operator <<(std::ostream& os, const gOrientato & go);
public:
    virtual ~gOrientato();
    gOrientato();
    gOrientato(const gOrientato &);
    gOrientato(const unsigned int &);//costruttore per creare 0 o più nodi nella stessa invocazione
    unsigned int GradoEntrante(const grafo::nodo &)const;
    unsigned int GradoUscente(const grafo::nodo &)const;
    virtual int TaglioMin()const;
    virtual int RicercaTaglioMin(int t)const;
    virtual bool NodoConnessoF(const nodo&)const;
    bool cammino(const nodo& ,const nodo&,std::list<grafo::nodo>&)const;
    virtual bool DebolmenteConnesso()const;
    virtual bool FortementeConnesso()const;
    virtual std::vector<grafo*> ComponentiConnesse()const;
    virtual gOrientato* ComponenteConnessa(const nodo &,std::vector<grafo::nodo>&)const;
    virtual bool Albero()const;
    std::vector<grafo*> ComponentiFortementeConnesse()const;
    int DFS(const grafo::nodo& ,std::list<grafo::nodo>&,std::list<int>& )const; //depth-first search
    gOrientato* DFS(std::list<grafo::nodo>&,std::list<int>& ,const grafo::nodo&)const;//depth-first search con percorso da seguire
    gOrientato trasposto()const;
    virtual gOrientato *ComplementoGrafo()const;
};


#endif // GORIENTATO_H
