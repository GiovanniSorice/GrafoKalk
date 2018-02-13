#include <spaziografo.h>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>
#include <math.h>
Nodo::Nodo(std::string info)
{
    QGraphicsTextItem * infoN=new QGraphicsTextItem (QString::fromStdString(info),this);

    QFont font=infoN->font();
    font.setPointSize(font.pointSize() + 5);
    infoN->setFont(font);
    infoN->setDefaultTextColor(QColor(Qt::white));
    infoN->setPos(-7,-7);
    setZValue(-1);
}

bool Nodo::operator ==(const Nodo &n)
{
    if(pos()==n.pos())
        return true;
    return false;
}

void Nodo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

        painter->setPen(QPen(Qt::black, 0));
        painter->setBrush(Qt::darkGray);
        painter->drawEllipse(-10,-10, 30, 30);
        QRadialGradient gradient(0, 0, 0);
        gradient.setColorAt(0, Qt::black);
        gradient.setColorAt(1, Qt::black);

        painter->setBrush(gradient);


}

QRectF Nodo::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

arco::arco(Nodo *sourceNode, Nodo *destNode):arrowSize(10)
{
    source = sourceNode;
    dest = destNode;
}

bool arco::operator ==(const Nodo &n)
{
    if(*source==n || *dest==n)
        return true;
    return false;
}

QRectF arco::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),destPoint.y() - sourcePoint.y())).normalized().adjusted(-extra, -extra, extra, extra);
}

void arco::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF lin(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = lin.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((lin.dx() * 10) / length, (lin.dy() * 10) / length);
        sourcePoint = lin.p1() + edgeOffset;
        destPoint = lin.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = lin.p1();
    }

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

SpazioGrafo::SpazioGrafo(QWidget *parent):QGraphicsView(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);

    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1), qreal(1));
    setMinimumSize(800, 400);

}

std::vector<Nodo *> SpazioGrafo::GetnodiSG() const
{
    return nodiSG;
}

void SpazioGrafo::cancellaUltimoNodo()
{
    for(std::vector<arco*>::iterator i=archiSG.begin(); i!=archiSG.end();){
        if(**i==*nodiSG.back()){
            delete *i;
            archiSG.erase(i);
        }else{
            i++;
        }
    }
    delete nodiSG.back();
   nodiSG.pop_back();
}

void SpazioGrafo::cancellaNodi()
{
    for(std::vector<Nodo*>::iterator i=nodiSG.begin();i!=nodiSG.end(); i++){
        delete *i;
    }
    nodiSG.clear();
}

void SpazioGrafo::aggiungiNodo(Nodo *n)
{
    nodiSG.push_back(n);
}

void SpazioGrafo::cancellaArchi()
{
    for(std::vector<arco*>::iterator i=archiSG.begin();i!=archiSG.end(); i++){
        delete *i;
    }
    archiSG.clear();
}

void SpazioGrafo::aggiungiArco(arco *a)
{
    archiSG.push_back(a);
}


