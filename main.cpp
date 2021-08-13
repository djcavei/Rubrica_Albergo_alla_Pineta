#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Albergo alla Pineta");
    QIcon icon(":/img/img/pineta.png");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
