#include "mainwindow.h"
#include "application.h"

int main(int argc, char *argv[])
{
    CRM::Application a(argc, argv);
    CRM::MainWindow w;
    w.setWindowTitle("Телефонный справочник");
    w.show();

    return a.exec();
}
