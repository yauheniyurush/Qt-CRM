#include "clientedit.h"

#include <QtSql>

namespace CRM {
namespace clients {
namespace client {

/*************************************************************/

Data::Data(QObject *parent, QSqlQuery &qry)
    : QObject(parent) {

    Id      = qry.value("iid"       ) ;
    Name    = qry.value("name"      ).toString() ;
    Surname   = qry.value("surname"   ).toString() ;
    pParentItem = 0;
    Deleted = false;

}
/*************************************************************/

Frame::Frame(QWidget *parent) :QFrame(parent){

    ui.setupUi(this);
    Block = 0;

}

Frame::~Frame(){

}

/** Тут сделать нормальную проверку данных */
void Frame::is_good(bool *pOK){
    *pOK = true;
}


void Frame::load() {
    if (!Block) return;
    ui.edtName->setText(Block->Name);
    ui.edtSurname->setText(Block->Surname);
}

bool Frame::save() {
    if (!Block) return false;
    Block->Name = ui.edtName->text().simplified();
    Block->Surname = ui.edtSurname->text().simplified();
    Block->Changed = true;
    return true;
}

Dialog::Dialog(QWidget *parent)
    : CommonDialog(parent) {
    {
        Frame *F = pFrame = new Frame(this);
        setCentralFrame(F);
    }
}

Dialog::~Dialog(){

}

bool Data::isActive() const {
    return true;
}

bool Data::isNew() const {

    if (! Id.isValid()) return true;
    if (Id.isNull()) return true;
    return false;
}

}//namespace client
}//namespace clients
}//namespace CRM
