#include "gorientato.h"

gOrientato::~gOrientato(){}

/*Costruttore a 0 elementi che richiama il costruttore a 0 elementi di grafo**/
gOrientato::gOrientato():grafo(){}

gOrientato::gOrientato(const gOrientato & gO):grafo(gO){}

/*Costruttore a 1 elemento che richiama il costruttore a 1 elemento di grafo**/
gOrientato::gOrientato(const unsigned int & n):grafo(n){}

unsigned int gOrientato::GradoEntrante(const grafo::nodo & n)const {
    if(TrovaNodo(n)==GetNodi().end()){
        throw eccezione("Nodo non presente nel grafo");
    }
    unsigned short int cont=0;
    std::vector<grafo::listaarchi> archi=GetAllArchi();
    for(std::vector<grafo::listaarchi>::const_iterator i=archi.begin();i!=archi.end();i++){
       std::list<nodo> la= i->GetListaA();
       for(std::list<nodo>::const_iterator c=la.begin();c!=la.end();c++){
           if(*c==n)
               cont++;
       }
    }
    return cont;
}

unsigned int gOrientato::GradoUscente(const grafo::nodo & n)const{
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
/***/
int gOrientato::TaglioMin()const{//cerca il nodo con il minor numero di archi associati
   int t=NNodi();
   gOrientato x=*this;
   if(t==1) return 0;
   t=x.RicercaTaglioMin(t);
   return t;
}
/*Ricerca il minimo numero di archi da togliere per avere un grafo disconnesso dal grafo originale**/
int gOrientato::RicercaTaglioMin(int t)const{
    if(t==0)return 0;
    if(!FortementeConnesso()) return 0;
    for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end() && t>1;i++){
      for(std::list<grafo::nodo>::const_iterator l=i->GetListaA().begin();l!=i->GetListaA().end() && t>1;l++){
        gOrientato x=*this;
        x.EliminaA(i->GetNod(),*l);
        int temp= x.RicercaTaglioMin(t-1)+1;
        if(temp<t)t=temp;
       }
    }
    return t;
}
/*Ridefinizione operatore di output << nodo **/
std::ostream& operator <<(std::ostream& os, const gOrientato & go){
    const grafo& g=go;
    return os<<g;
}
/*Funzione che controlla se un grafo è fortemente connesso**/
bool gOrientato::FortementeConnesso()const{
    for(std::vector<grafo::nodo>::const_iterator i=GetNodi().begin();i!=GetNodi().end();i++){
       if(!NodoConnessoF(*i))return false;
    }
    return true;
}
/*Funzione che controlla un nodo sia fortemente connesso agli altri**/
bool gOrientato::NodoConnessoF(const grafo::nodo& n)const{
    std::vector<grafo::nodo> v=GetNodi();
    v.erase(std::find(v.begin(),v.end(),n));
    for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end();i++){
        if(i->GetNod()==n){
            for(std::list<nodo>::const_iterator c=i->GetListaA().begin();c!=i->GetListaA().end();c++){
                v.erase(std::find(v.begin(),v.end(),*c));
            }
            break;
        }
    }
    if(v.empty())return true;
    // funzione che controlla nodo per nodo se c'è un cammino
    std::list<grafo::nodo> nodivisti;
    for(std::vector<grafo::nodo>::const_iterator i=v.begin();i!=v.end();i++){
        nodivisti.clear();
        if(!gOrientato::cammino(n,*i,nodivisti))
            return false;
    }
    return true;
}
/*Cerca un cammino orientato tra due nodi**/
bool gOrientato::cammino(const nodo &n, const nodo &n2,std::list<grafo::nodo>& v)const{
   std::list<nodo> ln;
    for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end();i++){
        if(i->GetNod()==n){
            ln= i->GetListaA();
            if(std::find(ln.begin(),ln.end(),n2)!=ln.end()){
                return true;
            };
            break;
        }
    }
    v.push_back(n);
    for(std::list<nodo>::const_iterator i=ln.begin();i!=ln.end();i++){
        if(std::find(v.begin(),v.end(),*i)==v.end())
            if(cammino(*i,n2,v))
                return true;
    }
    return false;
}

bool gOrientato::DebolmenteConnesso() const
{
    gOrientato temp=trasposto();
    temp+*this;
    return temp.grafo::DebolmenteConnesso();
}

bool gOrientato::Albero()const{
    if(!DebolmenteConnesso()){
        return false;
    }
    gOrientato temp=*this;
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for(std::vector<grafo::nodo>::const_iterator nodoCurr= nodiGrafo.begin();nodoCurr!=nodiGrafo.end();nodoCurr++) {//controllo che sia aciclico
        std::list<grafo::nodo> listTemp;
        if(cammino(*nodoCurr,*nodoCurr,listTemp)){
            return false;
        }
    }
    for(std::vector<grafo::nodo>::const_iterator nodoCurr= nodiGrafo.begin();nodoCurr!=nodiGrafo.end();nodoCurr++) {
        for(std::vector<grafo::nodo>::const_iterator nodoCurr2= nodiGrafo.begin();nodoCurr2!=nodiGrafo.end();nodoCurr2++) {
            if(temp.EliminaA(*nodoCurr,*nodoCurr2)){
                return !(temp.DebolmenteConnesso());
            }
        }
    }
    return false;
}
/*Funzione che ritorna tutte le componenti connesse di un grafo orientato**/
std::vector<grafo*> gOrientato::ComponentiConnesse()const{
  std::vector<grafo*> vg;
  std::vector<nodo> v;
  gOrientato grafoCompleto=trasposto();
  grafoCompleto+*this;
  for(std::vector<grafo::nodo>::const_iterator i=GetNodi().begin();i!=GetNodi().end();i++){
      if(std::find(v.begin(), v.end(),*i)==v.end()){
          gOrientato * go= grafoCompleto.ComponenteConnessa(*i,v);
          vg.push_back(go);
      }
  }
  return vg;
}
/*Funzione che ritorna la componente connessa di un determinato grafo**/
gOrientato* gOrientato::ComponenteConnessa(const nodo&n,std::vector<grafo::nodo>& v)const{
   if(std::find(v.begin(), v.end(),n)!=v.end()){
   gOrientato* g=new gOrientato();
   g->AggiungiN(GetInfo(n));
   return g;
   }
   for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin(); i!=GetAllArchi().end();i++){
        if(i->GetNod()==n){
            v.push_back(n);
            gOrientato* go=new gOrientato();
            go->AggiungiN(GetInfo(n));
            for(std::list<nodo>::const_iterator l=i->GetListaA().begin();l!=i->GetListaA().end();l++){
              gOrientato* goc=ComponenteConnessa(*l,v);
              *go+*goc;
              delete goc;
              go->AggiungiA(n,*l);
            }
            return go;
        }
    }
   return new gOrientato();
}
/*Funzione che ritorna le componenti fortemente connesse di un grafo orientato tramite l'lgoritmo di **/
std::vector<grafo *> gOrientato::ComponentiFortementeConnesse() const
{
    std::vector<grafo*> vg;
    std::list<grafo::nodo> v;
    std::list<int> nSottonodi;

    for(std::vector<grafo::nodo>::const_iterator c=GetNodi().begin();c!=GetNodi().end();c++){
        if(std::find(v.begin(), v.end(),*c)==v.end()){
            DFS(*c,v,nSottonodi);
        }
    }

    gOrientato gTrasposto=trasposto();

   while(v.begin()!=v.end()){
       std::list<grafo::nodo>::const_iterator i=v.begin();
       grafo::nodo temp=*i;
       gOrientato * go=gTrasposto.DFS(v,nSottonodi,temp);
       vg.push_back(go);
    }
   return vg;
}
/*Funzione che ritorna il sottografo fortemente connesso a partire da un nodo di un grafo orientato**/
int gOrientato::DFS(const grafo::nodo& n,std::list<grafo::nodo>& nodiVisitati,std::list<int>& numeroSottonodi) const
{
    if(std::find(nodiVisitati.begin(),nodiVisitati.end(),n)==nodiVisitati.end()){
        nodiVisitati.push_front(GetInfo(n));
        for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end();i++){
            int nSottonodi=0;
            if(*i==n){
              for(std::list<grafo::nodo>::const_iterator l=i->GetListaA().begin();l!=i->GetListaA().end();l++){
                  nSottonodi= DFS(*l,nodiVisitati,numeroSottonodi);
               }
              numeroSottonodi.push_back(nSottonodi);
              return nSottonodi+1;
            }
        }
    }
    return 0;

}
/*Funzione che ritorna il sottografo fortemente connesso a partire da un nodo di un grafo orientato seguendo uno specifico percorso**/
gOrientato* gOrientato::DFS(std::list<grafo::nodo>& ordineNodi,std::list<int>& numeroSottonodi,const grafo::nodo& n) const
{
    if(std::find(ordineNodi.begin(),ordineNodi.end(),n)!=ordineNodi.end()){
        ordineNodi.pop_front();
        int numeroSottonodiCurr=numeroSottonodi.front();
        numeroSottonodi.pop_front();
        for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end();i++){
            if(*i==n){
                gOrientato * go=new gOrientato();
                go->AggiungiN(GetInfo(n));
                std::list<grafo::nodo> cam;
                if(cammino(n,n,cam)){
                  for(std::list<grafo::nodo>::const_iterator l=i->GetListaA().begin();l!=i->GetListaA().end();l++){
                      std::list<grafo::nodo>::iterator iteOrdineNodi=ordineNodi.begin();
                      std::list<int>::iterator iteNumeroSottonodi=numeroSottonodi.begin();
                          std::list<grafo::nodo>::iterator iteUltimoNodoAlbero=ordineNodi.begin();
                          iteUltimoNodoAlbero++;//utilizzato come past the end della lista
                          for(int c=0;c<numeroSottonodiCurr-1;c++)
                              iteUltimoNodoAlbero++;
                          if(std::find(iteOrdineNodi,iteUltimoNodoAlbero,*l)!=iteUltimoNodoAlbero){
                              for(int conta=0;conta<numeroSottonodiCurr;conta++){
                                  if(*iteOrdineNodi==*l){
                                      if(iteOrdineNodi!=ordineNodi.begin()){
                                         ordineNodi.push_front(*iteOrdineNodi);
                                         ordineNodi.erase(iteOrdineNodi);
                                         numeroSottonodi.push_front(*iteNumeroSottonodi+conta);
                                         numeroSottonodi.erase(iteNumeroSottonodi);
                                      }
                                      break;
                                  }
                                  *iteNumeroSottonodi--;
                                  iteNumeroSottonodi++;
                                  iteOrdineNodi++;
                                  }
                              gOrientato * got= DFS(ordineNodi,numeroSottonodi,*l); //go temporaneo
                              *go+*got;
                              delete got;
                          }
                   }
                }
              return go;
            }
        }
    }
    return new gOrientato();

}

gOrientato gOrientato::trasposto()const
{
    gOrientato go;
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for(std::vector<grafo::nodo>::const_iterator i=nodiGrafo.begin();i!=nodiGrafo.end();i++){
        go.grafo::AggiungiN(GetInfo(*i));
    }
    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    for(std::vector<grafo::listaarchi>::const_iterator i=archiGrafo.begin();i!=archiGrafo.end();i++){
        std::list<grafo::nodo> archiNodo=i->GetListaA();
        nodo n=i->GetNod();
        for(std::list<grafo::nodo>::const_iterator l=archiNodo.begin();l!=archiNodo.end();l++)
            go.AggiungiA(*l,n);
    }
    return go;
}

gOrientato *gOrientato::ComplementoGrafo()const
{
    gOrientato* complemento=new gOrientato();
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for(std::vector<grafo::nodo>::const_iterator nodoCurr=nodiGrafo.begin();nodoCurr!=nodiGrafo.end();nodoCurr++) {
        complemento->AggiungiN(GetInfo(*nodoCurr));
    }
    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    for(std::vector<grafo::listaarchi>::const_iterator la=archiGrafo.begin();la!=archiGrafo.end();la++) {
        std::list<grafo::nodo> archiNodo=la->GetListaA();
        for(std::vector<grafo::nodo>::const_iterator nodoCurr=nodiGrafo.begin();nodoCurr!=nodiGrafo.end();nodoCurr++) {
            if(!(*la==*nodoCurr) && std::find(archiNodo.begin(),archiNodo.end(),*nodoCurr)==archiNodo.end()){
                complemento->AggiungiA(la->GetNod(),*nodoCurr);
            }
        }
    }
    return complemento;

}


