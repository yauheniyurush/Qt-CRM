#ifndef APPLICATION_H
#define APPLICATION_H


#include <QApplication>

namespace CRM {

class Application : public QApplication
{

    Q_OBJECT

public:
    Application( int argc, char *argv[]);
    virtual ~Application();
};

}//namespace CRM

#endif // APPLICATION_H
