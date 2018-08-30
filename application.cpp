#include "application.h"
#include <QtSql>

namespace CRM {

Application::Application(int argc, char *argv[]) :QApplication (argc, argv)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("store");
    //так указывать логин и пароль указывать нельзя
    db.open("admin","1");
}

Application::~Application(){

}

}
