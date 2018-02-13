#include <grafokalc.h>
#include <QIntValidator>
#include<QLabel>

GrafoQWidget::GrafoQWidget(QWidget * qw):QWidget(qw){
    grafoWidget=0;
    schermo = new QTextEdit(this);
    schermo->setReadOnly(true);
    schermo->setAlignment(Qt::AlignRight);
    schermo->setMaximumHeight(100);
    QFont font = schermo->font();
    font.setPointSize(font.pointSize() + 3);
    schermo->setFont(font);

    infoNodo1=new QLineEdit("",this);
    infoNodo2=new QLineEdit("",this);
    QLabel* label1=new QLabel("Campo info 1",this);
    QLabel* label2=new QLabel("Campo info 2",this);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    infoNodo1->setValidator(new QIntValidator(0, 2000, this));
    infoNodo2->setValidator(new QIntValidator(0, 2000, this));
    QWidget* mw=static_cast<QWidget*>(qw->parent());

    QPushButton *aggiungiN = createButton(tr("Aggiungi nodo"),mw, SLOT(aggiungiNodo()));
    QPushButton *eliminaN = createButton(tr("Elimina nodo"),mw, SLOT(eliminaNodo()));
    QPushButton *aggiungiA = createButton(tr("Aggiungi arco"),mw, SLOT(aggiungiArco()));
    QPushButton *eliminaA = createButton(tr("Elimina arco"),mw, SLOT(eliminaArco()));
    QPushButton *cammino = createButton(tr("Trova cammino"),mw, SLOT(cammino()));
    QPushButton *taglioM = createButton(tr("Taglio minimo grafo"),mw, SLOT(taglioMinimo()));
    QPushButton *connessoD = createButton(tr("Connesso debolmente"),mw, SLOT(connessoD()));
    QPushButton *albero = createButton(tr("Albero"),mw, SLOT(albero()));
    QPushButton *componentiConnesse = createButton(tr("Mostra le componenti connesse"),mw, SLOT(componentiConnesse()));
    QPushButton *nNodi = createButton(tr("Numero nodi"),mw, SLOT(nNodi()));
    QPushButton *nArchi = createButton(tr("Numero archi"),mw, SLOT(nArchi()));
    QPushButton *completaGrafo = createButton(tr("Completa il grafo"),mw, SLOT(completaGrafo()));
    QPushButton *scriviG = createButton(tr("Grafo to string"),mw, SLOT(scriviGrafo()));
    QPushButton *complemento = createButton(tr("Grafo complementare"),mw, SLOT(complementoGrafo()));
    QPushButton *eliminaG = createButton(tr("Cancella grafo"),mw, SLOT(eliminaGrafo()));
    scriviG->setMinimumSize(150,5);
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(schermo, 6, 0, 1, 6);
    mainLayout->addWidget(aggiungiN, 0, 0);
    mainLayout->addWidget(eliminaN, 0, 1);
    mainLayout->addWidget(aggiungiA, 0, 2);
    mainLayout->addWidget(label1, 0,3 );
    mainLayout->addWidget(infoNodo1, 0,4 );
    mainLayout->addWidget(label2, 1,3 );
    mainLayout->addWidget(infoNodo2, 1,4 );
    mainLayout->addWidget(eliminaA, 1, 0);
    mainLayout->addWidget(cammino, 1, 1);
    mainLayout->addWidget(taglioM, 1, 2);    
    mainLayout->addWidget(albero, 2, 0);
    mainLayout->addWidget(componentiConnesse, 2, 1);
    mainLayout->addWidget(nNodi, 2, 2);
    mainLayout->addWidget(nArchi, 3, 0);
    mainLayout->addWidget(completaGrafo, 3,1);
    mainLayout->addWidget(connessoD, 3, 2);
    mainLayout->addWidget(scriviG, 3, 3);
    mainLayout->addWidget(eliminaG, 3, 4);
    mainLayout->addWidget(complemento, 4, 0);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));

}

GrafoQWidget::~GrafoQWidget(){
    delete grafoWidget;
}

grafo *GrafoQWidget::getGrafo()const{return grafoWidget;}

void GrafoQWidget::setGrafo(grafo *g)
{
    delete grafoWidget;
    grafoWidget=g;
}

QString GrafoQWidget::getInfoNodo1()const{return infoNodo1->text();}

QString GrafoQWidget::getInfoNodo2()const{return infoNodo2->text();}

QTextEdit* GrafoQWidget::getSchermo()const{return schermo;}

SpazioGrafo *GrafoQWidget::getSgrafo() const{return sgrafo;}

QPushButton *GrafoQWidget::createButton(const QString & nome, QWidget * parent, const char * signal)
{
    QPushButton *button = new QPushButton(parent);
    button->setText(nome);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        connect(button, SIGNAL(clicked()), parent, signal);
        return button;
}




GOrientatoQWidget::GOrientatoQWidget(QWidget *qw):GrafoQWidget(qw)
{
    QWidget* mw=static_cast<QWidget*>(qw->parent());
    grafoWidget=new gOrientato();
    getSchermo()->setText(QString::fromStdString(grafoWidget->toString()));
    QPushButton *connessoF = createButton(tr("Connesso fortemente"),mw, SLOT(connessoF()));
    QPushButton *gradoEnt = createButton(tr("Grado entrante"),mw, SLOT(gradoE()));
    QPushButton *gradoUsc = createButton(tr("Grado uscente"),mw, SLOT(gradoE()));
    QPushButton *cfc = createButton(tr("Comp. fortemente con."),mw, SLOT(compFortConn()));
    sgrafo=new SpazioGrafo(this);
    QGridLayout *mainLayout = static_cast<QGridLayout*>(layout());

    mainLayout->addWidget(connessoF, 4, 1);
    mainLayout->addWidget(gradoEnt, 4, 2);
    mainLayout->addWidget(gradoUsc, 5, 0);
    mainLayout->addWidget(cfc, 5, 1);
    mainLayout->addWidget(sgrafo, 7, 0,1,6);
}

GNOrientatoQWidget::GNOrientatoQWidget(QWidget *qw):GrafoQWidget(qw)
{
    QWidget* mw=static_cast<QWidget*>(qw->parent());
    grafoWidget=new gNOrientato();
    getSchermo()->setText(QString::fromStdString(grafoWidget->toString()));
    QPushButton *planare = createButton(tr("Planare"),mw, SLOT(planare()));
    QPushButton *bipar = createButton(tr("Bipartito"),mw, SLOT(bipartito()));
    QPushButton *grado = createButton(tr("Grado nodo"),mw, SLOT(grado()));

    sgrafo=new SpazioGrafo(this);
    QGridLayout *mainLayout = static_cast<QGridLayout*>(layout());

    mainLayout->addWidget(planare, 4, 1);
    mainLayout->addWidget(bipar, 4, 2);
    mainLayout->addWidget(grado, 5, 0);
    mainLayout->addWidget(sgrafo, 7, 0,1,6);
}

GNOPlanareQWidget::GNOPlanareQWidget(QWidget * qw):GNOrientatoQWidget(qw)
{
    if(grafoWidget)
        delete grafoWidget;
    grafoWidget=new gNOPlanare();

    sgrafo=new SpazioGrafo(this);
    QGridLayout *mainLayout = static_cast<QGridLayout*>(layout());
    mainLayout->addWidget(sgrafo, 7, 0,1,6);
}
