#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <eccezione.h>
class grafo
{
protected:
    class nodo;
    class listaarchi;
public:
    friend std::ostream& operator<<(std::ostream& os, const grafo& );
    friend std::ostream& operator<<(std::ostream& os, const grafo::nodo& n);
    friend std::ostream& operator<<(std::ostream& os, const grafo::listaarchi& la);
protected:
    class nodo
    {
        friend std::ostream& operator<<(std::ostream& os, const grafo::nodo& n);
    public:
        unsigned int  info;
        nodo(const unsigned int & );
        bool operator==(const nodo & )const;
        bool operator<(const nodo&)const;
    };
    class listaarchi
    {
        friend std::ostream& operator<<(std::ostream& os, const grafo::listaarchi& la);
    public:
        nodo nod;
        std::list<nodo> la;
        listaarchi(const nodo & n);
        bool operator ==(const nodo & )const;
        const std::list<nodo>& GetListaA()const;
        const nodo& GetNod()const;
    };
private:
    std::vector<nodo> nodi;
    std::vector<listaarchi> archi;
    unsigned short int  nNodi;
    unsigned short int  nArchi;
public:
    grafo();
    grafo(const unsigned int &);//costruttore per creare 0 o più nodi nella stessa invocazione
    const std::vector<nodo>& GetNodi()const;
    const std::vector<listaarchi>& GetAllArchi()const;
    virtual ~grafo();
    grafo& operator+(const grafo &);
    unsigned int GetInfo(nodo) const;
    bool empty()const;
    virtual void AggiungiN();
    virtual void AggiungiN(unsigned int);
    bool EliminaN(const nodo &);
    void EliminaTA(const nodo &);//elimina tutti gli archi di un determinato nodo
    std::vector<nodo>::const_iterator TrovaNodo(const nodo &)const;
    int NNodi()const;
    virtual int NArchi()const;
    virtual void AggiungiA(const nodo &,const nodo &);// il bool serve a forzare la creazione di archi doppi o cappi che rendono il mio grafo non più semplice
    virtual bool EliminaA(const nodo &,const nodo &);// elimina uno specifico arco tra due nodi
    virtual int TaglioMin()const=0;
    virtual int RicercaTaglioMin(int t)const=0;
    bool NodoConnessoD(const nodo&)const;
    virtual bool DebolmenteConnesso()const;
    virtual std::vector<grafo*> ComponentiConnesse()const=0;
    virtual grafo* ComponenteConnessa(const nodo &,std::vector<grafo::nodo>&)const=0;
    virtual bool Albero()const=0;
    bool cammino(const nodo &, const nodo &) const;
    bool cammino(const nodo& ,const nodo&,std::list<nodo>&)const;
    virtual void CompletaGrafo();
    virtual grafo* ComplementoGrafo()const=0;
    void cancellaGrafo();
    std::string toString()const;
};
#endif // GRAFO_H
