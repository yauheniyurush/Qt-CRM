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
    Q_PROPERTY(QVariant Patronymic READ Patronymic )
    Q_PROPERTY(QVariant City READ City )
    Q_PROPERTY(QVariant Street READ Street )
    Q_PROPERTY(QVariant PhoneNumber READ PhoneNumber )

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
    QVariant Patronymic() const;
    QVariant City() const;
    QVariant Street() const;
    QVariant PhoneNumber() const;


signals:
    void apply_filter(QObject *pMainframe);

};

}//namespace CRM

#endif // MAINFRAME_H
