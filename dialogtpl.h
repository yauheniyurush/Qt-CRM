#ifndef DIALOGTPL_H
#define DIALOGTPL_H

#include "ui_buttonsframe.h"

#include <QFrame>
#include <QDialog>

namespace  CRM {

class ButtonsDlg : public QFrame {

    Q_OBJECT

public:
    ButtonsDlg(QWidget *parent=0);
    virtual ~ButtonsDlg();

public slots:
    void error_message (const QString &);

private:
    Ui::ButtonsFrame ui;

signals:
    void accepted();
    void rejected();

};

class CommonDialog: public QDialog {

    Q_OBJECT

private:
    ButtonsDlg *pButtons;
    QFrame     *pFrame;

private slots:
    void accept_pressed();

protected:
    void setCentralFrame(QFrame *central);

public:
    CommonDialog(QWidget *parent = 0) ;
    virtual ~CommonDialog();

signals:
    void check_data(bool *pOK);
    void save() ;

};

}//namespace  CRM

#endif // DIALOGTPL_H
