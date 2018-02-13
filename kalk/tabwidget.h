#ifndef TabWidget_H
#define TabWidget_H

#include <grafokalc.h>
#include <eccezione.h>
#include <QTabWidget>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *);
    //virtual ~TabWidget();
/*signals:
    void gtostring();
    void reloadG();
    void aggiornastatusbar(std::string);*/
/*public slots:
    void aggiungiNodo();
    void eliminaNodo();
    void aggiungiArco();
    void eliminaArco();
    void cammino();
    void taglioMinimo();
    void connessoD();
    void connessoF();
    void albero();
    void componentiConnesse();
    void nNodi();
    void nArchi();
    void completaGrafo();
    void planare();
    void scriviGrafo();
    void complementoGrafo();
    void eliminaGrafo();
    void gradoE();
    void gradoU();
    void compFortConn();
    void bipartito();
    void aggiornaGW(); //aggiorna la vista del grafo*/
private:
    //QTabWidget * PageWidget;
};
#endif // TabWidget_H


