#include<mainwindow.h>
#include <grafokalc.h>
#include <eccezione.h>
#include<qstatusbar.h>
#include <sstream>
#include <QMessageBox>
MainWindow::MainWindow()
{
    QTabWidget *tabwidget = new QTabWidget(this);
    tabwidget->addTab(new GOrientatoQWidget(tabwidget),"Grafo Orientato");
    tabwidget->addTab(new GNOrientatoQWidget(tabwidget),"Grafo non orientato");
    tabwidget->addTab(new GNOPlanareQWidget(tabwidget),"Grafo non orientato planare");

    setCentralWidget(tabwidget);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    statusBar()->showMessage("Clicca un pulsante per sapere cosa fa");
    setWindowTitle(tr("GrafoKalk"));
    setMinimumSize(825,800);
    setMaximumSize(1000,800);
    connect(this,SIGNAL(gtostring(QWidget*)),this,SLOT(scriviGrafo(QWidget*)));
    connect(this,SIGNAL(reloadG(QWidget*)),this,SLOT(aggiornaGW(QWidget*)));
    connect(this,SIGNAL(aggiornastatusbar(std::string)),this,SLOT(aStatusbar(std::string)));
}

void MainWindow::aStatusbar(std::string s)
{
    statusBar()->showMessage(QString::fromStdString(s));
}

bool MainWindow::posAcettabile(const std::vector<QPoint> & posPunti, const QPoint & pos)
{
    for(std::vector<QPoint>::const_iterator posCurr=posPunti.begin();posCurr!=posPunti.end();posCurr++)
    {
        int diffx=abs(pos.x())-abs(posCurr->x());
        int diffy=abs(pos.y())-abs(posCurr->y());
        if(diffx>-30 && diffx<30 && diffy>-30 && diffy<30)
            return false;
    }
     return true;
}

void MainWindow::aggiungiNodo()
{
    emit aggiornastatusbar("Aggiunge un nodo al grafo, possibilmente con l'info scritta nel campo info 1");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();
    bool ok;
    unsigned int infoN=currW->getInfoNodo1().toInt(&ok);
    try{
    if(ok)
        g->AggiungiN(infoN);
    else
        g->AggiungiN();
    emit gtostring(currW);
    emit reloadG(currW);
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
}

void MainWindow::eliminaNodo()
{
    emit aggiornastatusbar("Elimina il nodo con l'info indicata nel campo info 1, se esiste");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();
    bool ok;
    unsigned int infoN=currW->getInfoNodo1().toInt(&ok);
    try{
        if(ok){
            g->EliminaN(infoN);
            emit gtostring(currW);
            emit reloadG(currW);
        }
        else
            throw eccezione("Info nodo mancante, scrivilo nell'apposta cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }


}

void MainWindow::aggiungiArco()
{
    emit aggiornastatusbar("Aggiunge l'arco tra i nodi aventi info indicate nei campi appositi, se esistenti");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();
    bool ok1,ok2;
    unsigned int infoN1=currW->getInfoNodo1().toInt(&ok1);
    unsigned int infoN2=currW->getInfoNodo2().toInt(&ok2);
    try{
        if(ok1 && ok2){
            g->AggiungiA(infoN1,infoN2);
            emit gtostring(currW);
            emit reloadG(currW);
        }
        else
            throw eccezione("Info nodo mancante, scrivilo nell'apposta cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }

}

void MainWindow::eliminaArco()
{
    emit aggiornastatusbar("Elimina l'arco tra i nodi aventi info indicate nei campi appositi, se esistente");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();
    bool ok1,ok2;
    unsigned int infoN1=currW->getInfoNodo1().toInt(&ok1);
    unsigned int infoN2=currW->getInfoNodo2().toInt(&ok2);
    try{
        if(ok1 && ok2){
            g->EliminaA(infoN1,infoN2);
            emit gtostring(currW);
            emit reloadG(currW);
        }
        else
            throw eccezione("Info nodo mancante, scrivilo nell'apposita cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
}

void MainWindow::cammino()
{
    emit aggiornastatusbar("Cerca un cammino tra i nodi aventi info indicate nelle apposite celle");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();
    bool ok1,ok2;
    unsigned int infoN1=currW->getInfoNodo1().toInt(&ok1);
    unsigned int infoN2=currW->getInfoNodo2().toInt(&ok2);
    QTextEdit * schermo=currW->getSchermo();
    try{
        if(ok1 && ok2){
            if(g->cammino(infoN1,infoN2)){
                schermo->setText(QString::fromStdString("Cammino esistente"));
            }else{
                schermo->setText(QString::fromStdString("Cammino non esistente"));
            }
        }
        else
            throw eccezione("Info nodo mancante, scrivilo nell'apposta cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }

}

void MainWindow::taglioMinimo()
{
    emit aggiornastatusbar("Riporta a video il taglio minimo del grafo");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();
    QTextEdit * schermo=currW->getSchermo();
    schermo->setText(QString::fromStdString(NumberToString(g->TaglioMin())));
}

void MainWindow::connessoD()
{
    emit aggiornastatusbar("Verifica che il grafo sia debolmente connesso");
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(clickedButton->parent());
    grafo *g=currW->getGrafo();

    QTextEdit * schermo=currW->getSchermo();
    if(g->DebolmenteConnesso())
        schermo->setText(QString("Il grafo è debolmente connesso"));
    else
        schermo->setText(QString("Il grafo non è debolmente connesso"));
}

void MainWindow::connessoF()
{
    emit aggiornastatusbar("Verifica che il grafo sia fortemente connesso");
    GrafoQWidget* currW=static_cast<GOrientatoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gOrientato *g=static_cast<gOrientato*>(currW->getGrafo());

    QTextEdit * schermo=currW->getSchermo();
    if(g->FortementeConnesso())
        schermo->setText(QString("Il grafo è fortemente connesso"));
    else
        schermo->setText(QString("Il grafo non è fortemente connesso"));
}

void MainWindow::albero()
{
    emit aggiornastatusbar("Verifica che il grafo sia un albero");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();

    QTextEdit * schermo=currW->getSchermo();
    if(g->Albero())
        schermo->setText(QString("Il grafo è un albero"));
    else
        schermo->setText(QString("Il grafo non è un albero"));
}

void MainWindow::componentiConnesse()
{
    emit aggiornastatusbar("Riporta a video le componenti connesse del grafo");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();

    QTextEdit * schermo=currW->getSchermo();
    std::vector<grafo*> v=g->ComponentiConnesse();
    schermo->clear();
    std::string componentiString="";
    for(std::vector<grafo*>::iterator pgc=v.begin();pgc!=v.end();pgc++)//pgc è il puntatore al grafo corrente
        componentiString+=" Componente connessa: "+(*pgc)->toString();
    schermo->setText(QString::fromStdString(componentiString));
}

void MainWindow::nNodi()
{
    emit aggiornastatusbar("Mostra il numero di nodi del grafo");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();
    QTextEdit * schermo=currW->getSchermo();
    schermo->setText(QString::fromStdString(NumberToString(g->NNodi())));
}

void MainWindow::nArchi()
{
    emit aggiornastatusbar("Mostra il numero di archi del grafo");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();
    QTextEdit * schermo=currW->getSchermo();
    schermo->setText(QString::fromStdString(NumberToString(g->NArchi())));
}

void MainWindow::completaGrafo()
{
    emit aggiornastatusbar("Completa il grafo aggiungendo gli archi mancanti");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();
    try{
    g->CompletaGrafo();
    }catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
    emit gtostring(currW);
    emit reloadG(currW);
}

void MainWindow::planare()
{
    emit aggiornastatusbar("Controlla che il grafo sia planare");
    GrafoQWidget* currW=static_cast<GNOrientatoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gNOrientato *g=static_cast<gNOrientato*>(currW->getGrafo());

    QTextEdit * schermo=currW->getSchermo();
    if(g->planare())
        schermo->setText(QString("Il grafo è planare"));
    else
        schermo->setText(QString("Il grafo non è planare"));

}

void MainWindow::scriviGrafo(QWidget* currW)
{

     QTextEdit * schermo=static_cast<GrafoQWidget*>(currW)->getSchermo();
     schermo->setText(QString::fromStdString((static_cast<GrafoQWidget*>(currW)->getGrafo())->toString()));
}

void MainWindow::scriviGrafo()
{
    emit aggiornastatusbar("Mostra a video il grafo nella forma scritta (consulta la guida per le specifiche)");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    QTextEdit * schermo=static_cast<GrafoQWidget*>(currW)->getSchermo();
    schermo->setText(QString::fromStdString((static_cast<GrafoQWidget*>(currW)->getGrafo())->toString()));
}

void MainWindow::complementoGrafo()
{
    emit aggiornastatusbar("Esegue e mostra il complemento del grafo");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();
    try{
        currW->setGrafo(g->ComplementoGrafo());
    }catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
    emit gtostring(currW);
    emit reloadG(currW);
}

void MainWindow::eliminaGrafo()
{
    emit aggiornastatusbar("Cancella tutti i nodi e tutti gli archi del grafo");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *g=currW->getGrafo();
    g->cancellaGrafo();
    emit gtostring(currW);
    emit reloadG(currW);
}

void MainWindow::gradoE()
{
    emit aggiornastatusbar("Mostra il grado entrante del nodo avente l'info indicata nel campo apposito, se esiste");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gOrientato *g=static_cast<gOrientato*>(currW->getGrafo());
    bool ok;
    unsigned int infoN=currW->getInfoNodo1().toInt(&ok);
    try{
    if(ok){
        QTextEdit * schermo=currW->getSchermo();
        schermo->setText(QString::fromStdString(NumberToString(g->GradoEntrante(infoN))));
    }
    else
        throw eccezione("Info nodo mancante, scrivilo nell'apposta cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
}

void MainWindow::gradoU()
{
    emit aggiornastatusbar("Mostra il grado uscente del nodo avente l'info indicata nel campo apposito, se esiste");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gOrientato *g=static_cast<gOrientato*>(currW->getGrafo());
    bool ok;
    unsigned int infoN=currW->getInfoNodo1().toInt(&ok);
    try{
    if(ok){
        QTextEdit * schermo=currW->getSchermo();
        schermo->setText(QString::fromStdString(NumberToString(g->GradoUscente(infoN))));
    }else
        throw eccezione("Info nodo mancante, scrivilo nell'apposta cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
}

void MainWindow::grado()
{
    emit aggiornastatusbar("Mostra il grado del nodo avente l'info indicata nel campo apposito, se esiste");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gNOrientato *g=static_cast<gNOrientato*>(currW->getGrafo());
    bool ok;
    unsigned int infoN=currW->getInfoNodo1().toInt(&ok);
    try{
    if(ok){
        QTextEdit * schermo=currW->getSchermo();
        schermo->setText(QString::fromStdString(NumberToString(g->Grado(infoN))));
    }else
        throw eccezione("Info nodo mancante, scrivilo nell'apposta cella");
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
    }
}

void MainWindow::compFortConn()
{
    emit aggiornastatusbar("Mostra le componenti fortemente connesse del grafo");
    GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gOrientato *g=static_cast<gOrientato*>(currW->getGrafo());

    QTextEdit * schermo=currW->getSchermo();
    std::vector<grafo*> v=g->ComponentiFortementeConnesse();
    schermo->clear();
    std::string componentiFString="";
    for(std::vector<grafo*>::iterator pgc=v.begin();pgc!=v.end();pgc++)//pgc è il puntatore al grafo corrente
        componentiFString+=" Componente fortemente connessa: "+(*pgc)->toString();
    schermo->setText(QString::fromStdString(componentiFString));
}

void MainWindow::bipartito()
{
    emit aggiornastatusbar("Verifica che il grafo sia bipartito");
    GNOrientatoQWidget* currW=static_cast<GNOrientatoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    gNOrientato *g=static_cast<gNOrientato*>(currW->getGrafo());

    QTextEdit * schermo=currW->getSchermo();
    std::vector<int> v=g->bipartito();
    if(v.size()>0)
        schermo->setText(QString("Il grafo è bipartito ed è un k ")+QString::fromStdString(NumberToString(v[0]))+QString(" ")+QString::fromStdString(NumberToString(v[1])));
    else
        schermo->setText(QString("Il grafo non è bipartito"));
}

void MainWindow::aggiornaGW(QWidget* currW)
{
    //GrafoQWidget* currW=static_cast<GrafoQWidget*>(qobject_cast<QPushButton *>(sender())->parent());
    grafo *graf=static_cast<GrafoQWidget*>(currW)->getGrafo();
    SpazioGrafo *sg = static_cast<GrafoQWidget*>(currW)->getSgrafo();
    QGraphicsScene * scene=sg->scene();
    sg->cancellaNodi();
    sg->cancellaArchi();
    std::string g=graf->toString();
    std::vector<Nodo*> nodisg;
    int contaNodi=0;
    //sg->setMinimumSize(currW->size());
    std::vector<std::string> infoNodi;
    std::string::iterator carattereCurr=g.begin();
    std::vector<QPoint> posPunti;
    scene->update();
    for(bool ok=true;ok;carattereCurr++){
        if(*carattereCurr=='(')continue;

        std::string info="";
        while(*carattereCurr!=',' && *carattereCurr!=')'){
            info+=*carattereCurr;
            carattereCurr++;
        }

        if(info!=""){
            contaNodi++;
            infoNodi.push_back(info);
            Nodo * temp=new Nodo(info);
            sg->aggiungiNodo(temp);
            scene->addItem(temp);
        }

        if(*carattereCurr==')')ok=false;
    }

    for(bool ok=true;ok;carattereCurr++){
        if(*carattereCurr=='{')continue;
        if(*carattereCurr=='}')ok=false;
        if(*carattereCurr=='(')continue;

        std::string infon1="";
        std::string infon2="";
        while(*carattereCurr!=','&& ok){
            infon1+=*carattereCurr;
            carattereCurr++;
        }
        if(ok)carattereCurr++;
        while(*carattereCurr!=')' && ok){
            infon2+=*carattereCurr;
            carattereCurr++;
        }

        if(infon1!="" && infon2!=""){
            Nodo* n1=0;
            Nodo*n2=0;
            nodisg=sg->GetnodiSG();
            std::vector<Nodo*>::const_iterator n=nodisg.begin();
            for(std::vector<std::string>::iterator i=infoNodi.begin();i!=infoNodi.end() && (!n1 || !n2);i++,n++){
                if(*i==infon1)
                    n1=*n;
                if(*i==infon2)
                    n2=*n;
            }
            if(n1 && n2){
                arco * arc=new arco(n1, n2);
                scene->addItem(arc);
                sg->aggiungiArco(arc);
            }
        }

        if(*carattereCurr=='}')ok=false;
    }

    int h=sg->size().height();
    int w=sg->size().width();
    try{
        if(contaNodi>0){
            nodisg=sg->GetnodiSG();
            for(std::vector<Nodo*>::const_iterator i=nodisg.begin(); i!=nodisg.end();i++){
                int tentativi=1;
                bool b=true;
                while(tentativi<1000 && b){
                    tentativi++;
                    int x=rand()%(w-50)-(w/2-50);
                    int y=rand()%(h-50)-(h/2-50);
                    QPoint p=QPoint(qreal(x), qreal(y));
                    if(posAcettabile(posPunti,p)){
                        posPunti.push_back(p);
                        (*i)->setPos(p);
                        b=false;
                    }
                }
                if(tentativi>=1000)
                    throw eccezione("Impossibile aggiungere un nuovo nodo, spazio nella pagina esaurito");
            }
        }
    }
    catch(eccezione e){
        QMessageBox::information(this, QString("Error"), QString::fromStdString(e.getTesto()), QMessageBox::Ok);
        graf->EliminaN(atoi((infoNodi.back()).c_str()));
        sg->cancellaUltimoNodo();
    }
}

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }
