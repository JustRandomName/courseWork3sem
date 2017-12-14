#include <iostream>
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "expt.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    try{
    MainWindow* w  = new MainWindow;
    w->show();
    }catch(...){
        qDebug()<< "lol";
    }

    return a.exec();
}
