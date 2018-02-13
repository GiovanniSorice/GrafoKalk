#ifndef SPAZIOGRAFO_H
#define SPAZIOGRAFO_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <vector>

class Nodo;
class arco;

class SpazioGrafo : public QGraphicsView
{
    Q_OBJECT
private:
    std::vector<Nodo*> nodiSG;
    std::vector<arco*> archiSG;
public:
    SpazioGrafo(QWidget *);
    std::vector<Nodo *> GetnodiSG()const;
    void cancellaUltimoNodo();
    void cancellaNodi();
    void cancellaArchi();
    void aggiungiNodo(Nodo*);
    void aggiungiArco(arco*);
};


class Nodo : public QGraphicsItem
{
public:
    Nodo(std::string);
    bool operator ==(const Nodo&);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

class arco : public QGraphicsItem
{
public:
    arco(Nodo *sourceNode, Nodo*destNode);
    bool operator ==(const Nodo &);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
private:
    Nodo *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};
#endif // SPAZIOGRAFO_H
