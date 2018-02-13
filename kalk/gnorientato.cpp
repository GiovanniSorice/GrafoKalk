
#include "gnorientato.h"

/*Distruttore**/
gNOrientato::~gNOrientato(){}
/*Costruttore senza parametri**/
gNOrientato::gNOrientato(){}
/*Costruttore ad un parametro per la creazione di più nodi**/
gNOrientato::gNOrientato(int n):grafo(n){}
/*Costruttore di copia**/
gNOrientato::gNOrientato(const gNOrientato & g):grafo(g){}

void gNOrientato::AggiungiA(const nodo &n,const nodo & n1) //da capire se permettere grafi non semplici tramite b
{
    grafo::AggiungiA(n,n1);
    grafo::AggiungiA(n1,n);
}

bool gNOrientato::EliminaA(const nodo & n,const nodo & n1)
{
 return grafo::EliminaA(n,n1) && grafo::EliminaA(n1,n);
}

/***/
int gNOrientato::TaglioMin()const{//cerca il nodo con il minor numero di archi associati
   int t=NNodi();
   if(t==1) return 0;
   gNOrientato x=*this;
   t=x.RicercaTaglioMin(t);
   return t;
}
/*Ricerca il minimo numero di archi da togliere per avere un grafo disconnesso dal grafo originale**/
int gNOrientato::RicercaTaglioMin(int t)const{
    if(t==0)return 0;
    if(!DebolmenteConnesso()) return 0;
    for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end() && t>1;i++){
      for(std::list<grafo::nodo>::const_iterator l=i->GetListaA().begin();l!=i->GetListaA().end() && t>1;l++){
        gNOrientato x=*this;
        x.EliminaA(i->GetNod(),*l);
        int temp= x.RicercaTaglioMin(t-1)+1;
        if(temp<t)t=temp;
       }
    }
    return t;
}


bool gNOrientato::Albero() const
{
    return (DebolmenteConnesso() && (NNodi()-1)==NArchi());
}

std::vector<grafo *> gNOrientato::ComponentiConnesse() const
{
    std::vector<grafo*> vg;
    std::vector<nodo> v;
    for(std::vector<grafo::nodo>::const_iterator i=GetNodi().begin();i!=GetNodi().end();i++){
        if(std::find(v.begin(), v.end(),*i)==v.end()){
            gNOrientato * go= ComponenteConnessa(*i,v);
            vg.push_back(go);
        }
    }
    return vg;
}

gNOrientato* gNOrientato::ComponenteConnessa(const grafo::nodo &n, std::vector<grafo::nodo> &v) const
{
    if(std::find(v.begin(), v.end(),n)!=v.end()){
        gNOrientato* g=new gNOrientato();
        g->AggiungiN(GetInfo(n));
        return g;
    }
    for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin(); i!=GetAllArchi().end();i++){
         if(i->GetNod()==n){
             v.push_back(n);
             gNOrientato* go=new gNOrientato();
             go->AggiungiN(GetInfo(n));
             for(std::list<nodo>::const_iterator l=i->GetListaA().begin();l!=i->GetListaA().end();l++){
               gNOrientato* goc=ComponenteConnessa(*l,v);
               *go+*goc;
               delete goc;
               go->AggiungiA(n,*l);
             }
             return go;
         }
     }
    return 0;
}

gNOrientato *gNOrientato::ComplementoGrafo()const
{
    gNOrientato* complemento=new gNOrientato();
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for (std::vector<grafo::nodo>::const_iterator nodCurr=GetNodi().begin(); nodCurr!=GetNodi().end(); nodCurr++) {
        complemento->AggiungiN(GetInfo(*nodCurr));
    }
    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    for(std::vector<grafo::listaarchi>::const_iterator la=archiGrafo.begin(); la!=archiGrafo.end(); la++) {
        std::list<grafo::nodo> archiNodo=la->GetListaA();
        for( std::vector<grafo::nodo>::const_iterator nodCurr=nodiGrafo.begin();nodCurr!=nodiGrafo.end();nodCurr++) {
            if(!(*la==*nodCurr) && std::find(archiNodo.begin(),archiNodo.end(),*nodCurr)==archiNodo.end()){
                complemento->grafo::AggiungiA(la->GetNod(),*nodCurr);
            }
        }
    }
    return complemento;
}

int gNOrientato::NArchi() const
{
    return grafo::NArchi()/2;
}

bool gNOrientato::planare() const
{
 std::vector<grafo::nodo> nodik5;
 gNOrientato tempK=*this;
 gNOrientato tempBip=*this;
 if((3*NNodi()-6)<NArchi()){
     return false;
 }else if(tempK.k5(nodik5,GetNodi().front())){
     return false;
 }else if(tempBip.k33()){
     return false;
 }else{
     return true;
 }
 return false;
}

bool gNOrientato::k5(std::vector<grafo::nodo>& nodiVisti, const grafo::nodo & n)
{
 if(nodiVisti.size()==5)
     return true;
 if(NNodi()<5 && NArchi()<20)
     return false;
 if(std::find(nodiVisti.begin(),nodiVisti.end(),n)==nodiVisti.end()){
     for(std::vector<grafo::listaarchi>::const_iterator archiGrafo=GetAllArchi().begin(); (5-nodiVisti.size())<=NNodi() && archiGrafo!=GetAllArchi().end();archiGrafo++){
         if(*archiGrafo==n){
             for(std::list<grafo::nodo>::const_iterator archiNodo=archiGrafo->GetListaA().begin(); archiNodo!=archiGrafo->GetListaA().end();archiNodo++){
                nodiVisti.push_back(n);
                if(k5(nodiVisti,*archiNodo)){
                    std::vector<grafo::nodo>::iterator cit =std::find(nodiVisti.begin(),nodiVisti.end(),archiGrafo->GetNod());
                    if(cit!=nodiVisti.end())nodiVisti.erase(cit);
                    bool ok=true;
                    for(std::vector<grafo::nodo>::iterator it=nodiVisti.begin();it!=nodiVisti.end() &&ok;it++){
                        if(std::find(archiGrafo->GetListaA().begin(),archiGrafo->GetListaA().end(),*it)==archiGrafo->GetListaA().end())
                            ok=false;
                    }
                    if(ok)
                        return true;
                }else{
                    std::vector<grafo::nodo>::iterator cit =std::find(nodiVisti.begin(),nodiVisti.end(),archiGrafo->GetNod());
                    if(cit!=nodiVisti.end())nodiVisti.erase(cit);
                }
             }
             return false;
         }
     }
 }
 return false;
}

std::vector<int> gNOrientato::bipartito() const
{
    std::vector<grafo::nodo> neri;
    std::vector<grafo::nodo>rossi;
    std::vector<int> cardinalita;
    if(!empty() && bipartito(GetNodi().front(),neri,rossi) && neri.size()!=0 && rossi.size()!=0){
        cardinalita.push_back(neri.size());
        cardinalita.push_back(rossi.size());
    }
    return cardinalita;
}

bool gNOrientato::bipartito(const grafo::nodo& n, std::vector<grafo::nodo>& neri, std::vector<grafo::nodo>& rossi,bool colore) const
{ //true per nero false per rosso
    if(std::find(neri.begin(),neri.end(),n)!=neri.end()){
        return colore;
    }
    if(std::find(rossi.begin(),rossi.end(),n)!=rossi.end()){
        return !colore;
    }
    //sappiamo che non l'abbiamo ancora trovato quindi lo aggiungiamo ai nodi in base a colore e poi eploriamo i suoi archi se ne ha
    if(colore)
        neri.push_back(n);
    else
        rossi.push_back(n);

    for(std::vector<grafo::listaarchi>::const_iterator archiGrafo=GetAllArchi().begin();archiGrafo!=GetAllArchi().end();archiGrafo++){
        if(*archiGrafo==n){
            for(std::list<grafo::nodo>::const_iterator archiNodo=archiGrafo->GetListaA().begin();archiNodo!=archiGrafo->GetListaA().end();archiNodo++){
                if(!bipartito(*archiNodo,neri,rossi,!colore)){
                    return false;
                }
            }
            break;
        }
    }
    return true;
}

bool gNOrientato::bipartitoCompletoK33(std::vector<grafo::nodo> & nero)
{
    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    for(std::vector<grafo::listaarchi>::const_iterator i=archiGrafo.begin();i!=archiGrafo.end();i++){
       if(std::find(nero.begin(),nero.end(),i->GetNod())!=nero.end()){
           std::vector<int> trovatoNodo(i->GetListaA().size(),0);
           std::vector<int>::iterator posizioneTrovatoNodo=trovatoNodo.begin();
           for(std::vector<grafo::listaarchi>::const_iterator j=archiGrafo.begin();j!=archiGrafo.end();j++){
               std::list<grafo::nodo> archiNodoJ=j->GetListaA();
               if(i!=j && std::find(nero.begin(),nero.end(),j->GetNod())!=nero.end()){
                   for(std::list<grafo::nodo>::const_iterator archiNodoI=i->GetListaA().begin();archiNodoI!=i->GetListaA().end();archiNodoI++){
                       if(std::find(archiNodoJ.begin(),archiNodoJ.end(),*archiNodoI)!=archiNodoJ.end()){
                           (*posizioneTrovatoNodo)++;
                       }
                       posizioneTrovatoNodo++;
                   }
                   posizioneTrovatoNodo=trovatoNodo.begin();
               }
           }
           int conta=0;
           for(std::vector<int>::iterator k=trovatoNodo.begin();k!=trovatoNodo.end();k++){
               if(*k>=2){
                   conta++;
                   if(conta>2)
                       return true;
               }
           }
       }

    }
    return false;
}

bool gNOrientato::k33()
{
    if(NNodi()<6 && NArchi()<9)
        return false;

    std::vector<grafo::nodo> neri;
    std::vector<grafo::nodo> rossi;
    if(bipartito(GetNodi().front(),neri,rossi) && neri.size()>2 && rossi.size()>2){
        if(bipartitoCompletoK33(neri))
            return true;
    }
    for(std::vector<grafo::nodo>::const_iterator nodiGrafo=GetNodi().begin(); nodiGrafo!=GetNodi().end(); nodiGrafo++){
        gNOrientato temp=*this;
        temp.EliminaN(*nodiGrafo);
        neri.clear();
        rossi.clear();
        if(temp.bipartito(temp.GetNodi().front(),neri,rossi) && neri.size()>2 && rossi.size()>2){
            if(bipartitoCompletoK33(neri))
                return true;
        }
    }

    return false;

}

unsigned int gNOrientato::Grado(const grafo::nodo & n)const{
    if(TrovaNodo(n)==GetNodi().end()){
        throw eccezione("Nodo non presente nel grafo");
        return 0;
    }
    std::vector<listaarchi> archi=GetAllArchi();
    for(std::vector<listaarchi>::const_iterator i=archi.begin();i!=archi.end();i++){
       if(i->GetNod()==n){
        if(!(i->GetListaA().empty())) return i->GetListaA().size();
         else return 0;
       }
    }
    return 0;
}

