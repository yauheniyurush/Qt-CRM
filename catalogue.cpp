#include "catalogue.h"

#include <QAction>
#include <QMenu>
#include <QtSql>


#include "posaction.h"

namespace CRM {
namespace Catalogue {

/****************************************************************************/

Model::Model(QObject *parent) : QAbstractTableModel(parent) {

    QSqlQuery qry;
    qry.setForwardOnly(true);
    qry.prepare( "select      \n"
                   "iid,        \n"
                   "Code,       \n"
                   "Title,      \n"
                   "valid_from, \n"
                   "valid_to,   \n"
                   "is_local,   \n"
                   "acomment,   \n"
                   "rid_parent, \n"
                   "alevel      \n"
                   "from catalogue;");
    if (qry.exec()) {
        while(qry.next()){
            Item::Data *D = new Item::Data(this, qry);
            Cat.append(D);
        }
    } else {
        qCritical() << "Error";
        QSqlError Err = qry.lastError();
        qCritical() << Err.nativeErrorCode();
        qCritical() << Err.databaseText().toUtf8().data();
        qCritical() << Err.driverText().toUtf8().data();

    }


    //Это тестовый каталог. Заменить на настоящий
    /*
    {
        Item::Data *D = new Item::Data(this);
        D->Code = "111";
        D->Title = "Физика";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "222";
        D->Title = "Математика";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "333";
        D->Title = "Биология";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "444";
        D->Title = "Валеология";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = true ;
        Cat.append(D);
    }{
        Item::Data *D = new Item::Data(this);
        D->Code = "555";
        D->Title = "Литература";
        D->From = QDateTime::currentDateTime();
        D->To = QDateTime();
        D->IsLocal = false ;
        D->Comment = "Проверить правильность";
        Cat.append(D);
    }*/

}

Model::~Model(){

}

int Model::rowCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return Cat.size() ;//TODO заменить на правильное количество
    } else {
        return 0;
    }
}

/****************************************************************************/

int Model::columnCount(const QModelIndex &parent) const{
    if (! parent.isValid()) {
        return 6 ;
    } else {
        return 0;
    }
}

/****************************************************************************/

QVariant Model::dataDisplay(const QModelIndex &I) const{
    Item::Data *D = Cat[I.row()];
    switch (I.column() ) {
      case 0 : return D->Code ;
      case 1 : return D->Title ;
      case 2 : return D->From.isValid() ? D->From.toString("dd.MM.yyyy") : "" ;
      case 3 : return D->To.isValid() ? D->To.toString("dd.MM.yyyy") : "" ;
      case 4 : return D->IsLocal ? tr("LOCAL") : QString() ;
      case 5 : return D->Comment.isEmpty() ? QString() : tr("CMT") ;
      default : return QVariant();
    }
}

QVariant Model::dataTextAlignment(const QModelIndex &I) const{
    int Result = Qt::AlignVCenter;
    Result |= I.column() == 1 ? Qt::AlignLeft : Qt::AlignHCenter ;
    return Result;
}

Item::Data * Model::dataDataBlock(const QModelIndex &I) const {
    int R = I.row();
    if (R < 0 || R >= Cat.size()) return 0;
    return Cat[R];
}

QVariant Model::dataFont(const QModelIndex &I) const {
    Item::Data *D = dataDataBlock(I);
    if (!D) return QVariant();
    QFont F;
    if (D->Deleted) F.setStrikeOut(true);
    return F;
}

QVariant Model::dataForeground(const QModelIndex &I) const {
    Item::Data *D = dataDataBlock(I);
    if (!D) return QVariant();
    QColor Result = D->IsLocal ? QColor("blue") : QColor ("black") ;
    if (!D->isActive()) Result.setAlphaF(1.0/3.0);
    return Result;
    //if (!(D->To.isValid())) return QVariant();
    //if (D->To > QDateTime::currentDateTime()) {
    //    if (D->IsLocal) return QColor("#0000FF");
    //    else return QColor("#000000");
    //}
    //else {
    //    return QColor("#AAAAAA");
    //}

}

QVariant Model::dataToolTip(const QModelIndex &I) const {
    Item::Data *D = dataDataBlock(I);
    if (!D) return QVariant();
    switch (I.column()) case 2:{
        if (!D->To.isValid()) return QVariant();
        return tr("Valid to %1").arg(D->To.toString("dd.MM.yyyy"));

    default : return QVariant();
    }

    return QVariant("ToolTip");
}

QVariant Model::data(const QModelIndex &I, int role) const {

    switch (role) {
      case Qt::DisplayRole       : return dataDisplay(I);
      case Qt::TextAlignmentRole : return dataTextAlignment(I);
      case Qt::ForegroundRole    : return dataForeground(I);
      case Qt::FontRole          : return dataFont(I);
      case Qt::ToolTipRole          : return dataToolTip(I);
      //case Qt::UserRole          : return QVariant(dataDataBlock(I));
      case Qt::UserRole+1          : {
        Item::Data *D =dataDataBlock(I);
        if (!D) return false;
        return D->Deleted;
    }
      default : return QVariant();
    }

}

/****************************************************************************/

QVariant Model::headerData(int section,
                           Qt::Orientation orientation,
                           int role) const{
    if (orientation != Qt::Horizontal)
        return QAbstractTableModel::headerData(section,orientation,role);

    switch (role) {

    case Qt::DisplayRole :
    switch (section) {
      case 0 : return tr("Code")    ;
      case 1 : return tr("Title")   ;
      case 2 : return tr("From")    ;
      case 3 : return tr("To")      ;
      case 4 : return tr("Is Local");
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

    default : return QVariant();

    }

}

void Model::delItem( const QModelIndex &I, QWidget *parent){
    //спросить у пользователя уверен ли он что хочет удалить элемент
    Item::Data *D = dataDataBlock(I);
    if (!D) return;
    //to do исходим из того что модель линейна
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    if (D->Id.isNull() || !D->Id.isValid()) {
    Cat.removeAt(I.row());
    delete D;
    } else {
        D->Deleted = ! D->Deleted;
    }
    endResetModel();//окончание редактирвоания данных
}

void Model::editItem( const QModelIndex &I, QWidget *parent){
    Item::Dialog Dia( parent );
    Item::Data *D = dataDataBlock(I);
    if (!D) return;
    Dia.setDataBlock(D);
    beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
    Dia.exec();
    endResetModel();//окончание редактирвоания данных
}

void Model::newItem( const QModelIndex &parentI, QWidget *parent){
    if (parentI.isValid()) {
        //Сделать добавление нового элемента не обязательно в корень каталога
        qWarning()<<"Cannot add non top-level item";
        return;
    }
    Item::Data *D = new Item::Data(this);
    if (!D) {
        qWarning() << "Cannot create new item";
        return;
    }
    Item::Dialog Dia( parent );
    Dia.setDataBlock(D);
    if (Dia.exec() == QDialog::Accepted) {
        beginResetModel();//модель отправляет всем представлениям связанным с данной моделью сигнал о том что данные редактируются и представления не могут запрашивать данные на редактирование
        Cat.append(D);
        endResetModel();//окончание редактирвоания данных
    } else {
        delete D;
    }
}
/****************************************************************************/
TableView::TableView(QWidget *parent) :QTableView(parent){

    Model *M = new Model(this);
    setModel( M );

    {
        QHeaderView *H = verticalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
    }{
        QHeaderView *H = horizontalHeader() ;
        H->setSectionResizeMode(QHeaderView::ResizeToContents);//автоподбор высоты строк + высоту строк нельзя будет изменять
        H->setSectionResizeMode(1,QHeaderView::Stretch);
    }


    //вызов окна редактирования для строки по действию

    setContextMenuPolicy(Qt::CustomContextMenu);//объявили политику всплывающего меню

    connect(this,SIGNAL(customContextMenuRequested(QPoint)), //связали экшн вызова меню с нашим акшн contextMenuRequested
            this,SLOT(contextMenuRequested(QPoint)));

    {
        PosAction *A = actDelItem = new PosAction(this);
        A->setText(tr("delete"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(delItem(QModelIndex,QWidget*)) );
        addAction(A);
    }

    {
        PosAction *A = actNewItem = new PosAction(this);
        A->setText(tr("add"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(newItem(QModelIndex,QWidget*)) );
        addAction(A);
    }

    {
        PosAction *A = actEditItem =new PosAction(this);
        A->setText(tr("Edit"));
        connect(A,SIGNAL(editItem(QModelIndex,QWidget*)),
                M,SLOT(editItem(QModelIndex,QWidget*)) );
        addAction(A);
    }
    //скрытие колонки
    setColumnHidden(3, true);
    setColumnHidden(4, true);

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
        actDelItem->I=I;
        actDelItem->pWidget=this;
        if (I.data(Qt::UserRole+1).toBool() ) {
            actDelItem->setText(tr("Restore"));
        }  else
        {
           actDelItem->setText(tr("Delete"));
        }
        M.addAction(actDelItem);
        actEditItem->I=I;
        actEditItem->pWidget = this;
        M.addAction(actEditItem);

    }
    actNewItem->I=QModelIndex();
    actNewItem->pWidget=this;
    M.addAction(actNewItem);
    M.exec(mapToGlobal(p));
}
/****************************************************************************/
}//Catalogue
}//namespace CRM
