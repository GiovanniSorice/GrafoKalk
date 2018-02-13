#include "gnoplanare.h"

/*Costruttore di default**/
gNOPlanare::gNOPlanare(){}
/*Costruttore ad un parametro per la creazione di più nodi**/
gNOPlanare::gNOPlanare(int n):gNOrientato(n){}
/*Costruttore di copia**/
gNOPlanare::gNOPlanare(const gNOPlanare &g):gNOrientato(g){}

gNOPlanare::gNOPlanare(const gNOrientato & g):gNOrientato(g){}

void gNOPlanare::AggiungiA(const grafo::nodo &n, const grafo::nodo &n1)
{
    gNOPlanare temp=*this;
    temp.gNOrientato::AggiungiA(n,n1);
    if(temp.planare()){
        gNOrientato::AggiungiA(n,n1);
    }else{
        throw eccezione("L'arco rende il grafo non planare");
    }
}

gNOPlanare *gNOPlanare::ComplementoGrafo() const
{
    bool e=false;
    gNOPlanare* complemento=new gNOPlanare();
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for (std::vector<grafo::nodo>::const_iterator nodCurr=GetNodi().begin(); nodCurr!=GetNodi().end(); nodCurr++) {
        complemento->AggiungiN(GetInfo(*nodCurr));
    }

    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    for(std::vector<grafo::listaarchi>::const_iterator la=archiGrafo.begin(); la!=archiGrafo.end(); la++) {
        std::list<grafo::nodo> archiNodo=la->GetListaA();
        for( std::vector<grafo::nodo>::const_iterator nodCurr=nodiGrafo.begin();nodCurr!=nodiGrafo.end();nodCurr++) {
            if(!(*la==*nodCurr) && std::find(archiNodo.begin(),archiNodo.end(),*nodCurr)==archiNodo.end()){
                try{
                complemento->AggiungiA(la->GetNod(),*nodCurr);
                }catch(eccezione){
                    if(!e)e=true;
                }
            }
        }
    }
    //if(e)throw eccezione("Uno o più archi non sono stati aggiunti perchè rendevano il grafo non planare");
    return complemento;
}

void gNOPlanare::CompletaGrafo() //usato perchè altrimenti l'eccezione dell'aggiunta degli archi non farebbe finire completamente la costruzione del grafo
{
    bool e=false;
    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for(std::vector<grafo::listaarchi>::const_iterator i=archiGrafo.begin();i!=archiGrafo.end();i++){
        std::list<grafo::nodo> archiNodo=i->GetListaA();
        for(std::vector<grafo::nodo>::const_iterator l=nodiGrafo.begin();l!=nodiGrafo.end();l++){
            if(!(*i==*l) && std::find(archiNodo.begin(),archiNodo.end(),*l)==archiNodo.end()){
                try{
                AggiungiA(i->GetNod(),*l);
                }catch(eccezione ){
                   if(!e)e=true;
                }
            }
        }
    }
    //if(e)throw eccezione("Uno o più archi non sono stati aggiunti perchè rendevano il grafo non planare");
}



