#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CRM::MainWindow w;
    w.showMaximized();

    return a.exec();
}
