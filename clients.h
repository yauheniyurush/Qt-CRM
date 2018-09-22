#ifndef clients_H
#define clients_H

#include <QAbstractTableModel>
#include <QTableView>
#include "clientedit.h"

class QAction;

namespace CRM {
    class PosAction;
}

namespace CRM {
namespace clients {

/****************************************************************************/
class Model: public QAbstractTableModel {

    Q_OBJECT

private:
    client::List Cat;
    QVariant fName;
    QVariant fSurname;
    QVariant fPatronymic;
    QVariant fPhoneNumber;
    QVariant fCity;
    QVariant fStreet;
    void adjust_query();

protected:
    virtual QVariant dataDisplay(const QModelIndex &I) const;
    virtual QVariant dataTextAlignment(const QModelIndex &I) const;
    virtual QVariant dataForeground(const QModelIndex &I) const;
    virtual QVariant dataFont(const QModelIndex &I) const;
    virtual QVariant dataToolTip(const QModelIndex &I) const;
    virtual client::Data * dataDataBlock(const QModelIndex &I) const;

public:
    Model(QObject *parent = 0);
    virtual ~ Model();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &I, int role) const ;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;

private:
    //удаление
    bool delete_all_from_db(client::Data *D = 0);//удаление из базы
    bool delete_all_from_model(client::Data *D = 0);//удаление из модели
    //сохранение изменений
    bool save_all_to_db(client::Data *D=0);//сохраняем изменения
    bool drop_change_mark(client::Data *D=0);//удаляем флаг что элемент менялся
    bool insert_all_to_db(client::Data *D=0);//сохраняем новые элементы
    bool adjust_id_for_new(client::Data *D=0);//сохраняем новые элементы

protected:
    bool delete_all(); //основная функция удаления
    bool save_all();   //основная функция сохранения
    bool insert_all(); //основная функция добавления

public slots:
    //изменение в модели
    void editItem(const QModelIndex &I      , QWidget *parent=0);
    void newItem (const QModelIndex &parentI, QWidget *parent=0);
    void delItem (const QModelIndex &I      , QWidget *parent=0);
    //сохранение изменений в базу
    void save();
    //фильтер
    void apply_filter(QObject *F);
};

/****************************************************************************/

class TableView : public QTableView {

    Q_OBJECT

private:
    PosAction *actEditItem; //вызов окна редактирования для выбранной строки
    PosAction *actNewItem ;
    PosAction *actDelItem ;
    QAction   *actSave;//экшн по сохранению

public:
    TableView(QWidget *parent=0);
    virtual ~ TableView();


private slots:
    void contextMenuRequested(const QPoint &p) ;
};


/****************************************************************************/
}//clients
}//namespace CRM

#endif // clients_H
