#include <tabwidget.h>
#include <sstream>
#include <math.h>
#include <QMessageBox>
TabWidget::TabWidget(QWidget * parent):QTabWidget(parent)
{
    addTab(new GOrientatoQWidget(this),"Grafo Orientato");
    addTab(new GNOrientatoQWidget(this),"Grafo non orientato");
    addTab(new GNOPlanareQWidget(this),"Grafo non orientato planare");
}
