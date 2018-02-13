#ifndef GRAFOKALC_H
#define GRAFOKALC_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include "gorientato.h"
#include "gnoplanare.h"
#include "spaziografo.h"
class QLineEdit;
class MainQWidget;
class GrafoQWidget : public QWidget
{
    Q_OBJECT
public:
    GrafoQWidget(QWidget *);
    virtual ~GrafoQWidget()=0;
    grafo *getGrafo() const;
    void setGrafo( grafo *);
    QString getInfoNodo1() const;
    QString getInfoNodo2() const;
    QTextEdit* getSchermo() const;
    SpazioGrafo *getSgrafo() const;

protected:
    QPushButton *createButton(const QString &,  QWidget *, const char *);
    grafo * grafoWidget;
    SpazioGrafo * sgrafo;
private:

    QTextEdit *schermo;
    QLineEdit *infoNodo1;
    QLineEdit *infoNodo2;
};

class GOrientatoQWidget : public GrafoQWidget
{
    Q_OBJECT
public:
    GOrientatoQWidget(QWidget *);
};
class GNOrientatoQWidget : public GrafoQWidget
{
    Q_OBJECT
public:
    GNOrientatoQWidget(QWidget *);
};

class GNOPlanareQWidget : public GNOrientatoQWidget
{
    Q_OBJECT
public:
    GNOPlanareQWidget(QWidget *);
};




#endif // GRAFOKALC_H
