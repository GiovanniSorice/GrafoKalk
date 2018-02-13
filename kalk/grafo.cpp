#include "grafo.h"
#include <sstream>
/*Funzione che ritorna l'info del nodo**/
unsigned int grafo::GetInfo(nodo n)const{return n.info;}

/*Funzione che indica se un grafo è vuoto**/
bool grafo::empty()const{
    return nodi.empty();
}

/*Overloading operatore== per classe nodo**/
bool grafo::nodo::operator==(const nodo& n)const{return info==n.info;}

bool grafo::nodo::operator<(const grafo::nodo & n) const{return info<n.info;}

/*Costruttore ad un parametro const unsigned short int per la classe nodo, il valore va a costituire il valore assegnato al campo info**/
grafo::nodo::nodo(const unsigned int & x ):info(x){}

/*Costruttore ad un parametro di listaarchi che collega la lista degli archi ad un nodo specifico**/
grafo::listaarchi::listaarchi(const nodo & n):nod(n),la(){}

/*Funzione che controlla se la lista degli archi appartiene a quel determinato nodo **/
//bool grafo::listaarchi::EqualNodo(const nodo & n)const{return *nod==n;}

/*Overloading operatore== per classe listaarchi con parametro const nodo & per comparazioni sul nodo avente la lista degli archi**/
bool grafo::listaarchi::operator ==(const grafo::nodo& n )const{return nod==n;}

/*Ritona il numero degli archi al momento dell'invocazione su una determinata istanza della classe grafo**/
int grafo::NArchi()const{return nArchi;}

/*Ritona il numero dei nodi al momento dell'invocazione su una determinata istanza della classe grafo**/
int grafo::NNodi()const{return nNodi;}

/*Funziona che ritorna la lista degli archi **/
const std::list<grafo::nodo>& grafo::listaarchi::GetListaA()const{return la;}
/*Funzione che ritorna nod**/
const grafo::nodo& grafo::listaarchi::GetNod()const{return nod;}
grafo::~grafo(){}

/*Costruttore a 0 parametri**/
grafo::grafo():nodi(),archi(),nNodi(0),nArchi(0){}

/*Costruttore ad un parametro che costruisce n nodi **/
grafo::grafo(const unsigned int & n):nNodi(0),nArchi(0){
    while(nNodi<n){
        AggiungiN();
    }
}
/*overloading operator + di grafo, aggiunge i nodi e gli archi non esistenti in in *this   **/
grafo& grafo::operator +(const grafo & g){
    for(std::vector<grafo::nodo>::const_iterator i=g.GetNodi().begin();i!=g.GetNodi().end();i++){
        if(std::find(GetNodi().begin(),GetNodi().end(),*i)==GetNodi().end())
            this->AggiungiN(GetInfo(*i));
    }
    for(std::vector<grafo::listaarchi>::const_iterator i=g.GetAllArchi().begin(); i!=g.GetAllArchi().end();i++){
            for(std::vector<grafo::listaarchi>::const_iterator l=GetAllArchi().begin();l!=GetAllArchi().end();l++){
                if(l->GetNod()==i->GetNod()){
                    for(std::list<grafo::nodo>::const_iterator m=i->GetListaA().begin();m!=i->GetListaA().end();m++){
                        if(std::find(l->GetListaA().begin(),l->GetListaA().end(),*m)==l->GetListaA().end()){
                            AggiungiA(i->GetNod(),*m);
                        }
                    }
                    break;
                }
            }
        }
    return *this;
    }
/*Funzione che aggiunge al grafo un nodo e crea la sua lista di archi**/
void grafo::AggiungiN()
{
    unsigned int nInfo=0;
    while(std::find(GetNodi().begin(),GetNodi().end(),nodo(nInfo))!=GetNodi().end())
        nInfo++;

    nodi.push_back((nodo(nInfo)));
    archi.push_back(listaarchi(nodi.back()));
    nNodi++;
}
/*Funzione che aggiunge al grafo un nodo con uno specifico info e crea la sua lista di archi**/
void grafo::AggiungiN(unsigned int i)
{
    if(std::find(GetNodi().begin(),GetNodi().end(),nodo(i))!=GetNodi().end()){
        throw eccezione("Nodo già presente");
    }
    nodi.push_back((nodo(i)));
    archi.push_back(listaarchi(nodi.back()));
    nNodi++;
}
/* Funzione che cerca il nodo nel grafo e se lo trova restituisce la sua posizione nel vector, altrimenti ritorna -1**/
std::vector<grafo::nodo>::const_iterator grafo::TrovaNodo(const nodo & n)const{
   for(std::vector<nodo>::const_iterator i=nodi.begin();i!=nodi.end();i++){
        if((*i)==n){
            return i;
        }
    }
    return nodi.end();
}
/* Funzione che elimina tutti gli archi collegati ad un determinato nodo **/
void grafo::EliminaTA(const nodo &n){
    for(std::vector<grafo::listaarchi>::iterator i=archi.begin();i!=archi.end();){
         if(*i==n){
             nArchi-=i->GetListaA().size();
             i=archi.erase(i);
         }
         else{
             if(!i->la.empty()){
                 std::list<nodo>::iterator ln=(i->la).begin();
                 std::list<nodo>::iterator fine=(i->la).end();
                 while(ln!=(i->la).end() && i->la.size()>0){
                    if(n==*ln){
                        ln=(i->la).erase(ln);
                        nArchi--;
                    }else{
                        ln++;
                    }
                 }
             }
             i++;
         }
    }
}
/* Funzione che elimina un nodo e tutto ciò che gli è collegato (archi) **/
bool grafo::EliminaN(const nodo & n){
    std::vector<nodo>::const_iterator i=TrovaNodo(n);
    if(i==nodi.end()){
        throw eccezione("Nodo non presente");
    }
    EliminaTA(n);
    nodi.erase(std::find(nodi.begin(),nodi.end(),n));
    nNodi--;
    return true;
}

/*Funzione che aggiunge un singolo arco**/
void grafo::AggiungiA(const nodo & n, const nodo &n1){
    std::vector<nodo>::const_iterator i1=TrovaNodo(n1);
    if(TrovaNodo(n)==nodi.end() ||i1== nodi.end()){
        throw eccezione("Nodo non è presente nel grafo");
    }

    for(std::vector<grafo::listaarchi>::iterator l=archi.begin();l!=archi.end();l++){
        if(l->nod==n){
            if(std::find(l->la.begin(),l->la.end(),n1)==l->la.end()){
            l->la.push_back(*i1);
            nArchi++;
            }
            return;
        }
    }
}
/*Funzione che elimina l'arco tra i due nodi n ed n1 se esiste**/
bool grafo::EliminaA(const nodo & n, const nodo & n1){
    if(TrovaNodo(n)==nodi.end() ||TrovaNodo(n1)== nodi.end()){
        throw eccezione("Nodo non è presente nel grafo");
    }
    for(std::vector<grafo::listaarchi>::iterator l=archi.begin();l!=archi.end();l++){
        if(l->nod==n && !(l->la.empty())){
            std::list<grafo::nodo> archiNodo=l->GetListaA();
            if(std::find(archiNodo.begin(),archiNodo.end(),n1)!=archiNodo.end()){
                    l->la.remove(n1);
                nArchi--;
                return true;
            }
            return false;
        }
    }
    return false;
}
/*Funzione che controlla un nodo sia debolmente connesso agli altri**/
bool grafo::NodoConnessoD(const grafo::nodo & n) const
{
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
        if(!(grafo::cammino(n,*i,nodivisti))){
            nodivisti.clear();
                if(!(grafo::cammino(*i,n,nodivisti)))
                    return false;
        }
    }
    return true;
}
/*Funzione che controlla la connessione del grafo**/
bool grafo::DebolmenteConnesso() const
{
    for(std::vector<grafo::nodo>::const_iterator i=GetNodi().begin();i!=GetNodi().end();i++){
       if(!NodoConnessoD(*i))return false;
    }
    return true;
}
//Ritorna il l'intero vettore degli archi
const std::vector<grafo::listaarchi>& grafo::GetAllArchi()const{return archi;}
const std::vector<grafo::nodo>& grafo::GetNodi()const{return nodi;}

/*Ridefinizione operatore di output per grafo <<**/
std::ostream& operator <<(std::ostream& os, const grafo & g){
    os<<"(";
    for(std::vector<grafo::nodo>::const_iterator i=g.GetNodi().begin();i!=g.GetNodi().end();i++){
    os<<*i;
    if(!(*i==g.GetNodi().back()))
        os<<",";
    }
    os<<")";
    os<<"{";
    for(std::vector<grafo::listaarchi>::const_iterator i=g.GetAllArchi().begin();i!=g.GetAllArchi().end();i++){
     os<<*i;
    }
    os<<"}";
    return os;
}

/*Ridefinizione operatore di output << nodo **/
std::ostream& operator <<(std::ostream& os, const grafo::nodo & n){
    return os<<n.info;
}

/*Ridefinizione operatore di output << listaarchi**/
std::ostream& operator <<(std::ostream& os, const grafo::listaarchi & la){
    if(!la.la.empty()){
        for(std::list<grafo::nodo>::const_iterator i=la.la.begin();i!=la.la.end();i++){
            os<<"("<<la.GetNod()<<","<<*i<<")";
        }
    }
    return os;

}

bool grafo::cammino(const nodo &n, const nodo &n1) const{
    std::list<grafo::nodo> v;
    return cammino(n,n1,v);
}

/*Cerca un cammino tra due nodi**/
bool grafo::cammino(const nodo &n, const nodo &n2,std::list<nodo>& v)const{
   std::list<nodo> ln;
   bool a=false, b=false;
    for(std::vector<grafo::listaarchi>::const_iterator i=GetAllArchi().begin();i!=GetAllArchi().end() && !(a&&b);i++){
        if(i->GetNod()==n){
           a=true;
            ln= i->GetListaA();
            if(std::find(ln.begin(),ln.end(),n2)!=ln.end()){
                return true;
            };
        }else
        if(i->GetNod()==n2){
            b=true;
            if(std::find(i->GetListaA().begin(),i->GetListaA().end(),n)!=i->GetListaA().end()){
                return true;
            };
        }
    }
    v.push_back(n);
    std::list<nodo> v2(v);
    for(std::list<nodo>::const_iterator i=ln.begin();i!=ln.end();i++){
        if(std::find(v.begin(),v.end(),*i)==v.end() && std::find(v2.begin(),v2.end(),*i)==v2.end())
            if(cammino(*i,n2,v) || cammino(n2,*i,v2))
                return true;
    }

    return false;
}

void grafo::CompletaGrafo()
{
    std::vector<grafo::listaarchi> archiGrafo=GetAllArchi();
    std::vector<grafo::nodo> nodiGrafo=GetNodi();
    for(std::vector<grafo::listaarchi>::const_iterator i=archiGrafo.begin();i!=archiGrafo.end();i++){
        std::list<grafo::nodo> archiNodo=i->GetListaA();
        for(std::vector<grafo::nodo>::const_iterator l=nodiGrafo.begin();l!=nodiGrafo.end();l++){
            if(!(*i==*l) && std::find(archiNodo.begin(),archiNodo.end(),*l)==archiNodo.end()){
                AggiungiA(i->GetNod(),*l);
            }
        }
    }
}

void grafo::cancellaGrafo()
{
    nodi.clear();
    archi.clear();
    nNodi=0;
    nArchi=0;
}

std::string grafo::toString()const
{
    std::ostringstream s;
    s<<*this;
    return s.str();
}
