#ifndef CLIENTEDIT_H
#define CLIENTEDIT_H

#include "ui_catitemframe.h"

#include <QFrame>
#include "dialogtpl.h"




class QSqlQuery;

namespace CRM {
namespace clients {
namespace client {

/***************************************************/
class Data;
class List : public QList<Data*> {
public:
    List() : QList<Data*>() {}
};

class Data : public QObject {

    Q_OBJECT

public:
    Data(QObject *parent=0):QObject(parent), pParentItem(0), Deleted(false) {}
    Data(QObject *parent, QSqlQuery &qry);
    QVariant  Id     ;
    QString   Name   ;
    QString   Surname;
    QString   Patronymic;
    QString   PhoneType;
    QString   PhoneNumber;
    QString   City;
    QString   Street;
    QString   LastpartAdress;
    QVariant   pParentItem ;
    bool    Deleted;
    bool    isActive() const;
    bool      isNew() const   ;
    bool      Changed     ; //параметр показывает редактировался ли объект

};


/***************************************************/
class Frame : public QFrame {

    Q_OBJECT

public:
    Frame(QWidget *parent=0);
    virtual ~Frame();

private:
  Ui::CatItemFrame ui;

public:
  Data *Block ;

public:
  void setDataBlock(Data *D) {
      Block = D;
      load();
  }

public slots:
  void is_good(bool *pOK);
  void load() ;//perenos inf s dannih na dialog
  bool save() ;//perenos inf s dialoga na dannie

signals:
  void error_message(const QString &);



};

/***************************************************/
class Dialog: public CommonDialog {

    Q_OBJECT

private:
    Frame *pFrame;

public:
    Dialog(QWidget *parent=0);
    virtual ~Dialog();

public:
    void setDataBlock(Data *D){
        pFrame->setDataBlock(D);
    }

};

/***************************************************/




} // namespace client
} // namespace clients
} // namespace CRM

#endif // CLIENTEDIT_H
