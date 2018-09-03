#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "ui_mainframe.h"
#include <QFrame>

namespace CRM {

class mainframe: public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QVariant name READ name )
    Q_PROPERTY(QVariant surname READ surname )

public:
    mainframe(QWidget *parent=0);
    virtual ~mainframe(){};
private:
    Ui::mainFrame ui;
private slots:
    void apply_filter_triggered();

public:
    QVariant name() const;
    QVariant surname() const;

signals:
    void apply_filter(QObject *pMainframe);

};

}//namespace CRM

#endif // MAINFRAME_H
