#include "gorientato.h"
#include "gnoplanare.h"
#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return a.exec();
}
