#include "application.h"
#include <QtSql>

namespace CRM {

Application::Application(int argc, char *argv[]) :QApplication (argc, argv)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL") ;
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("CRM");
    //так указывать логин и пароль нельзя
    db.open("admin","1");
}

Application::~Application(){

}

}
