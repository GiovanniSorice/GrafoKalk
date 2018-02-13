#ifndef GNOPLANARE_H
#define GNOPLANARE_H
#include "gnorientato.h"

class gNOPlanare :public gNOrientato
{
public:
    gNOPlanare();
    gNOPlanare(int);//costruttore per creare 0 o più nodi nella stessa invocazione
    gNOPlanare(const gNOPlanare&);
    gNOPlanare(const gNOrientato&);
    virtual void AggiungiA(const nodo &,const nodo &);
    virtual gNOPlanare *ComplementoGrafo()const;
    void CompletaGrafo();
};


#endif // GNOPLANARE_H
