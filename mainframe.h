#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "ui_mainframe.h"
#include <QFrame>

namespace CRM {

class mainframe: public QFrame
{
public:
    mainframe(QWidget *parent=0);
    virtual ~mainframe(){};
private:
    Ui::mainFrame ui;
};

}//namespace CRM

#endif // MAINFRAME_H
