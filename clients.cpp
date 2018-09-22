#include "clients.h"

#include <QAction>
#include <QMenu>
#include <QtSql>
#include <QMessageBox>

#include "posaction.h"

namespace CRM {
namespace clients {

/****************************************************************************/

Model::Model(QObject *parent) : QAbstractTableModel(parent) {

    QSqlQuery qry;
    qry.setForwardOnly(true);
    qry.prepare("select s.iid, name, surname, patronymic, \n"
                "p.phonetype, p.phonenumber, \n"
                "a.city, a.street, a.lastpartadress \n"
                "from clients s \n"
                "left outer join phone_numbers p on p.iid = s.iid \n"
                "left outer join adress a on a.iid = s.iid");
    if (qry.exec()) {
        while(qry.next()){
            client::Data *D = new client::Data(this, qry);
            Cat.append(D);
        }
    } else {
        qCritical() << "Error";
        QSqlError Err = qry.lastError();
        qCritical() << Err.nativeErrorCode();
        qCritical() << Err.databaseText().toUtf8().data();
        qCritical() << Err.driverText().toUtf8().data();
    }
}

/*------------------------------------------------------------------------------*/
Model::~Model(){

}

/*------------------------------------------------------------------------------*/
int Model::rowCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return Cat.size() ;//TODO заменить на правильное количество
    } else {
        return 0;
    }
}


/*------------------------------------------------------------------------------*/
int Model::columnCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return 8 ;
    } else {
        return 0;
    }
}

//методы по отображению информации

/*------------------------------------------------------------------------------*/
QVariant Model::dataDisplay(const QModelIndex &I) const{
    client::Data *D = Cat[I.row()];
    switch (I.column() ) {
      case 2 : return D->Name ;
      case 3 : return D->Surname ;
      case 4 : return D->Patronymic;
      case 0 : return D->PhoneType;
      case 1 : return D->PhoneNumber;
      case 5 : return D->City;
      case 6 : return D->Street;
      case 7 : return D->LastpartAdress;
     default : return QVariant();
    }
}

/*------------------------------------------------------------------------------*/
QVariant Model::dataTextAlignment(const QModelIndex &I) const{
    int Result = Qt::AlignVCenter;
    Result |= I.column() == 1 ? Qt::AlignLeft : Qt::AlignHCenter ;
    return Result;
}

/*------------------------------------------------------------------------------*/
client::Data * Model::dataDataBlock(const QModelIndex &I) const {
    int R = I.row();
    if (R < 0 || R >= Cat.size()) return 0;
    return Cat[R];
}

/*------------------------------------------------------------------------------*/
QVariant Model::dataFont(const QModelIndex &I) const {
    client::Data *D = dataDataBlock(I);
    if (!D) return QVariant();
    QFont F;
    F.setPointSize(7);
    if (D->Deleted) F.setStrikeOut(true);
    return F;
}

/*------------------------------------------------------------------------------*/
QVariant Model::dataForeground(const QModelIndex &I) const {
    client::Data *D = dataDataBlock(I);
    if (!D) return QVariant();
    QColor Result = QColor ("black") ;
    //Result.setAlphaF(1.0/3.0);
    return Result;
}

/*------------------------------------------------------------------------------*/
QVariant Model::dataToolTip(const QModelIndex &I) const {
/*    client::Data *D = dataDataBlock(I);
    if (!D) return QVariant();
    switch (I.column()) case 2:{
        if (!D->To.isValid()) return QVariant();
        return tr("Valid to %1").arg(D->To.toString("dd.MM.yyyy"));

    default : return QVariant();
    }
*/
    return QVariant("ToolTip");
}

/*------------------------------------------------------------------------------*/
QVariant Model::data(const QModelIndex &I, int role) const {

    switch (role) {
      case Qt::DisplayRole       : return dataDisplay(I);
      case Qt::TextAlignmentRole : return dataTextAlignment(I);
      case Qt::ForegroundRole    : return dataForeground(I);
      case Qt::FontRole          : return dataFont(I);
      case Qt::ToolTipRole          : return dataToolTip(I);
      //case Qt::UserRole          : return QVariant(dataDataBlock(I));
      case Qt::UserRole+1          : {
        client::Data *D =dataDataBlock(I);
        if (!D) return false;
        return D->Deleted;
    }
      default : return QVariant();
    }

}

/*------------------------------------------------------------------------------*/
QVariant Model::headerData(int section,
                           Qt::Orientation orientation,
                           int role) const{
    if (orientation != Qt::Horizontal)
        return QAbstractTableModel::headerData(section,orientation,role);

    switch (role) {

    case Qt::DisplayRole :
    switch (section) {
      case 0 : return tr("Тип")    ;
      case 1 : return tr("Телефон")   ;
      case 2 : return tr("Имя")   ;
      case 3 : return tr("Фамилия")   ;
      case 4 : return tr("Отчество")   ;
      case 5 : return tr("Город")   ;
      case 6 : return tr("Улица")   ;
      case 7 : return tr("Доп. адр.")   ;
      default : return QVariant()   ;
    }

    case Qt::TextAlignmentRole :
        return QVariant(Qt::AlignBaseline | Qt::AlignCenter) ;

    case Qt::ForegroundRole :
    { //Сделать шрифт жирным
        QFont F;
        F.setBold(true);
        return F;
    }
    case Qt::FontRole :
    {
        QFont F;
        F.setPointSize(7);
        return F;
    }

    default : return QVariant();

    }

}

/*------------------------------------------------------------------------------*/

void Model::delItem( const QModelIndex &I, QWidget *parent){
    //спросить у пользователя уверен ли он что хочет удалить элемент
    client::Data *D = dataDataBlock(I);
    if (!D) return;
    //to do исходим из того что модель линейна
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    if (D->Id.isNull()) {
    Cat.removeAt(I.row());
    delete D;
    } else {
        D->Deleted = ! D->Deleted;
    }
    endResetModel();//окончание редактирвоания данных
}

void Model::editItem( const QModelIndex &I, QWidget *parent){
    client::Dialog Dia( parent );
    client::Data *D = dataDataBlock(I);
    if (!D) return;
    Dia.setDataBlock(D);
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    Dia.exec();
    endResetModel();//окончание редактирвоания данных
}

void Model::newItem( const QModelIndex &parentI, QWidget *parent){
    client::Data *D = new client::Data(this);
    if (!D) {
        qWarning() << "Cannot create new item";
        return;
    }
    client::Dialog Dia( parent );
    Dia.setDataBlock(D);
    if (Dia.exec() == QDialog::Accepted) {
        beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
        Cat.append(D);
        endResetModel();//окончание редактирвоания данных
    } else {
        delete D;
    }
}

void Model::save(){
    try {
    if (!delete_all()) throw (int)1;//удалить все элементы помеченные для удал
    if (!save_all()  ) throw (int)2;//сохранить измененённые эл-ты
    if (!insert_all()  ) throw (int)3;//сохранить новые эл-ты
    QMessageBox::information(0,tr("Info"),tr("Сохранено"));
    //сохранить новые элементы
    } catch (int x){
        QMessageBox::critical(0, tr("Error"), tr("Ошибка сохранения"));
    }
}

//функция для удаления из базы данных
bool Model::delete_all_from_db(client::Data *D) {
    client::List *Cl =  &Cat ;
    client::Data *X;
    foreach (X, *Cl) {
    if (X->Deleted) {
            {
                QSqlQuery DEL ;
                DEL.setForwardOnly(true);
                DEL.prepare("Delete from adress where iid = :IID ;");
                DEL.bindValue(":IID", X->Id) ;
                if (!DEL.exec()) {
                qCritical() << DEL.lastError().databaseText();
                qCritical() << DEL.lastError().driverText();
                qCritical() << DEL.lastError().nativeErrorCode();
                return false ;
                }
            }
        {
            QSqlQuery DEL ;
            DEL.setForwardOnly(true);
            DEL.prepare("Delete from phone_numbers where iid = :IID ;");
            DEL.bindValue(":IID", X->Id) ;
            if (!DEL.exec()) {
            qCritical() << DEL.lastError().databaseText();
            qCritical() << DEL.lastError().driverText();
            qCritical() << DEL.lastError().nativeErrorCode();
            return false ;
            }
        }
        {
            QSqlQuery DEL ;
            DEL.setForwardOnly(true);
            DEL.prepare("Delete from clients where iid = :IID ;");
            DEL.bindValue(":IID", X->Id) ;
            if (!DEL.exec()) {
            qCritical() << DEL.lastError().databaseText();
            qCritical() << DEL.lastError().driverText();
            qCritical() << DEL.lastError().nativeErrorCode();
            return false ;
            }
        }
     }
    }
    return true;
}



//функция для удаления из модели
bool Model::delete_all_from_model(client::Data *D) {
    bool Result = true;
    client::List *Cl = &Cat ;
    beginResetModel();
    for (int k = Cl->size()-1; k>=0; k--) {
        if (Cl->at(k)->Deleted) {
         client::Data *X = Cl->takeAt(k);
        delete X;
        }
    }
    endResetModel();
    return Result;
}

//основная функция для удаления
bool Model::delete_all() {
    bool R = true ;
    QSqlDatabase DB = QSqlDatabase::database();
    DB.transaction();
    if (delete_all_from_db())
    {
        DB.commit();
        return delete_all_from_model();
    }
    else {
        DB.rollback();
        return false;
    }
}

//сохраняем изменения
bool Model::save_all_to_db(client::Data *D){
    client::List *Cl =  &Cat ;
    client::Data *X;
    foreach (X, *Cl) {
        if (X->Changed) {
            QSqlQuery UPD ;
            UPD.setForwardOnly(true);
            UPD.prepare("update clients set   \n"
                         "name       = :NAME   , \n"
                         "surname      = :SURNAME \n"
                         "where iid  = :IID        ");
            UPD.bindValue(":NAME"   , X->Name   ) ;
            UPD.bindValue(":SURNAME"  , X->Surname  ) ;
            UPD.bindValue(":IID"    , X->Id     ) ;

            if (!UPD .exec()) {
                qCritical() << UPD.executedQuery();
                qCritical() << UPD.lastError().databaseText();
                qCritical() << UPD.lastError().driverText();
                qCritical() << UPD.lastError().nativeErrorCode();
                return false ;
            }
        }
    }
    return true;
}
//удаляем флаг что элемент менялся
bool Model::drop_change_mark(client::Data *D){
    client::List *Cl =  &Cat ;
    client::Data *X;
    foreach (X, *Cl) {
        if (X->Changed == true) X->Changed = false;
    }
    return true;
}

//основная функция удаления
bool Model::save_all(){
    QSqlDatabase DB = QSqlDatabase::database();
    DB.transaction();
    if (save_all_to_db())
    {
        DB.commit();
        return drop_change_mark();
    }
    else {
        DB.rollback();
        return false;
    }
}

//сохраняем новые элементы
bool Model::insert_all_to_db(client::Data *D){
    client::List *Cl =  &Cat ;
    client::Data *X;
    QVariant Id;
    foreach (X, *Cl) {
    bool must_be_saved = X ? X->isNew() : false;
        if (must_be_saved) {
        QSqlQuery INS ;
        INS.setForwardOnly(true);
        INS.prepare("insert into clients (\n"
                    "name, surname, patronymic  \n"
                    ") values (             \n"
                    ":NAME, :SURNAME, :PATRONYMIC        \n"
                    ")returning iid;        \n"
                    );
        INS.bindValue(":NAME"   , X->Name   ) ;
        INS.bindValue(":SURNAME", X->Surname) ;
        INS.bindValue(":PATRONYMIC", X->Patronymic) ;
        if (!INS .exec()) {
            qCritical() << INS.lastError().databaseText().toUtf8().data();
            qCritical() << INS.lastError().driverText();
            qCritical() << INS.lastError().nativeErrorCode();
            return false;
        }
        while (INS.next()) {
            Id = INS.value("iid");
        }
        //вставляем адрес
        INS.setForwardOnly(true);
        INS.prepare("insert into adress (                \n"
                    "iid, city, street, lastpartadress   \n"
                    ") values (                          \n"
                    ":IID, :CITY, :STREET, :LASTPARTADRESS\n"
                    ");                                  \n");
        INS.bindValue(":IID"   , Id) ;
        INS.bindValue(":CITY", X->City) ;
        INS.bindValue(":STREET", X->Street) ;
        INS.bindValue(":LASTPARTADRESS", X->LastpartAdress) ;
        if (!INS .exec()) {
            qCritical() << INS.lastError().databaseText().toUtf8().data();
            qCritical() << INS.lastError().driverText();
            qCritical() << INS.lastError().nativeErrorCode();
            return false;
        }

        //вставляем номер телефона
        INS.setForwardOnly(true);
        INS.prepare("insert into phone_numbers (         \n"
                    "iid, phonetype, phonenumber         \n"
                    ") values (                          \n"
                    ":IID, :PHONETYPE, :PHONENUMBER      \n"
                    ");                                  \n");
        INS.bindValue(":IID"        , Id);
        INS.bindValue(":PHONETYPE"  , X->PhoneType);
        INS.bindValue(":PHONENUMBER", X->PhoneNumber);
        if (!INS .exec()) {
            qCritical() << INS.lastError().databaseText().toUtf8().data();
            qCritical() << INS.lastError().driverText();
            qCritical() << INS.lastError().nativeErrorCode();
            return false;
        }
        X->setProperty("new_id", Id);
    }
    }
    return true;
}

//сохраняем новые элементы
bool Model::adjust_id_for_new(client::Data *D){
    client::List *Cl =  &Cat ;
    client::Data *X;
    foreach (X, *Cl) {
    bool must_be_saved = X ? X->isNew() : false;
    if (must_be_saved) {
        X->Id = X->property("new_id");
    }
    }
    return true;
}

//основная функция добавления
bool Model::insert_all(){
    QSqlDatabase DB = QSqlDatabase::database();
    DB.transaction();
    if (insert_all_to_db())
    {
        DB.commit();
        return adjust_id_for_new();
    }
    else {
        DB.rollback();
        return false;
    }
}

/****************************************************************************/

TableView::TableView(QWidget *parent) :QTableView(parent){

    Model *M = new Model(this);
    setModel( M );

    //{
    //    QHeaderView *H = verticalHeader() ;
    //    H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
    //}
    {
        QHeaderView *H = horizontalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
        //H->setSectionResizeMode(2,QHeaderView::Stretch);
    }


    //вызов окна редактирования для строки по действию
    setContextMenuPolicy(Qt::CustomContextMenu);//объявили политику всплывающего меню

    //связали экшн вызова меню с нашим акшн contextMenuRequested
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(contextMenuRequested(QPoint)));

    {
        PosAction *A = actDelItem = new PosAction(this);
        A->setText(tr("Удалить"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(delItem(QModelIndex,QWidget*)) );
        this->addAction(A);
    }

    {
        PosAction *A = actNewItem = new PosAction(this);
        A->setText(tr("Добавить"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(newItem(QModelIndex,QWidget*)) );
        this->addAction(A);
    }

    {
        PosAction *A = actEditItem =new PosAction(this);
        A->setText(tr("Редактировать"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(editItem(QModelIndex,QWidget*)) );
        this->addAction(A);
    }
    {
        QAction *A = actSave =new QAction(this);
        A->setText(tr("Сохранить"));
        connect(A,SIGNAL(triggered()),
                M,SLOT(save()) );
        this->addAction(A);
    }
    //скрытие колонки
    //setColumnHidden(3, true);
    //setColumnHidden(4, true);

}

TableView::~TableView(){

}

//вызов окна редактирования Слот для action
//void TableView::editItem(){
//}

//пишем свою функцию по отображению меню
void TableView::contextMenuRequested(const QPoint &p) {
    QMenu M(this);
    QModelIndex I = indexAt(p);
    if (I.isValid()) {
        //удаление-восстановление
        actDelItem->I=I;
        actDelItem->pWidget=this;
        if (I.data(Qt::UserRole+1).toBool() ) {
            actDelItem->setText(tr("Восстановление"));
        }  else
        {
           actDelItem->setText(tr("Удаление"));
        }
        M.addAction(actDelItem);
        //редактирование
        actEditItem->I=I;
        actEditItem->pWidget = this;
        M.addAction(actEditItem);
    }
    //новый элемент
    actNewItem->I=QModelIndex();
    actNewItem->pWidget=this;
    M.addAction(actNewItem);
    M.addAction(actSave);//экшн по сохранению
    M.exec(mapToGlobal(p));
}
/*------------------------------------------------------------------------------*/
//фильтер
void Model::apply_filter(QObject *F){
    fName = F->property("name");
    fSurname = F->property("surname");
    fPatronymic = F->property("Patronymic");
    fPhoneNumber = F->property("PhoneNumber");
    fCity = F->property("City");
    fStreet = F->property("Street");
    adjust_query();
}

void Model::adjust_query(){
    QString QueryText = "select s.iid, name, surname, patronymic, \n"
                        "p.phonetype, p.phonenumber, \n"
                        "a.city, a.street, a.lastpartadress \n"
                        "from clients s \n"
                        "left outer join phone_numbers p on p.iid = s.iid \n"
                        "left outer join adress a on a.iid = s.iid \n"
                        "where 1=1      ";
     if (fName.isValid()) QueryText += "and name ~ :NAME \n";
     if (fSurname.isValid()) QueryText += "and surname ~ :SURNAME \n";
     if (fPatronymic.isValid()) QueryText += "and patronymic ~ :PATRONYMIC \n";
     if (fCity.isValid()) QueryText += "and city ~ :CITY \n";
     if (fStreet.isValid()) QueryText += "and street ~ :STREET \n";
     if (fPhoneNumber.isValid()) QueryText += "and phonenumber ~ :PHONENUMBER \n";
     QueryText += "; \n";

     QSqlQuery qry;
     qry.prepare(QueryText);
     if (fName.isValid()) qry.bindValue(":NAME","^"+fName.toString());
     if (fSurname.isValid()) qry.bindValue(":SURNAME","^"+fSurname.toString());
     if (fPatronymic.isValid()) qry.bindValue(":PATRONYMIC","^"+fPatronymic.toString());
     if (fCity.isValid()) qry.bindValue(":CITY","^"+fCity.toString());
     if (fStreet.isValid()) qry.bindValue(":STREET","^"+fStreet.toString());
     if (fPhoneNumber.isValid()) qry.bindValue(":PHONENUMBER","^"+fPhoneNumber.toString());


     if ( !qry.exec() ) {
         qCritical() <<  qry.lastError().databaseText().toUtf8().data();
     } else {
         client::List *Cl = &Cat ;
         beginResetModel();
         for (int k = Cl->size()-1; k>=0; k--) {
              client::Data *X = Cl->takeAt(k);
             delete X;

         }
         endResetModel();
         while(qry.next()){
             client::Data *D = new client::Data(this, qry);
             Cat.append(D);
         }
     }
}

/****************************************************************************/
}//clients
}//namespace CRM
