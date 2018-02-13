#include <QMainWindow>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    bool posAcettabile(const std::vector<QPoint>&,const QPoint &);
signals:
    void gtostring(QWidget*);
    void reloadG(QWidget*);
    void aggiornastatusbar(std::string);
public slots:
    void aStatusbar(std::string);
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
    void scriviGrafo(QWidget*);
    void scriviGrafo();
    void complementoGrafo();
    void eliminaGrafo();
    void gradoE();
    void gradoU();
    void grado();
    void compFortConn();
    void bipartito();
    void aggiornaGW(QWidget*); //aggiorna la vista del grafo
};

#endif // MAINWINDOW_H

#ifndef numbertostring
#define numbertostring
template <class T>
  std::string NumberToString ( T );
#endif // numbertostring
