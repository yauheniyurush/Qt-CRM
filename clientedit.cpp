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
    this->Patronymic = qry.value("patronymic"   ).toString() ;
    this->Street = qry.value("street").toString();
    this->City = qry.value("city").toString();
    this->LastpartAdress = qry.value("lastpartadress").toString();
    this->PhoneNumber = qry.value("phonenumber").toString();
    this->PhoneType = qry.value("phonetype").toString();
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
    ui.lineEditAddInf->setText(Block->LastpartAdress);
    ui.lineEditCity->setText(Block->City);
    ui.lineEditPatronymic->setText(Block->Patronymic);
    ui.lineEditPhoneNumb->setText(Block->PhoneNumber);
    ui.lineEditPhoneType->setText(Block->PhoneType);
    ui.lineEditStreet->setText(Block->Street);
}

bool Frame::save() {
    if (!Block) return false;
    Block->Name = ui.edtName->text().simplified();
    Block->Surname = ui.edtSurname->text().simplified();
    Block->Changed = true;
    Block->Patronymic = ui.lineEditPatronymic->text().simplified();
    Block->Street = ui.lineEditStreet->text().simplified();
    Block->City = ui.lineEditCity->text().simplified();
    Block->LastpartAdress = ui.lineEditAddInf->text().simplified();
    Block->PhoneNumber = ui.lineEditPhoneNumb->text().simplified();
    Block->PhoneType = ui.lineEditPhoneType->text().simplified();
    return true;
}

Dialog::Dialog(QWidget *parent)
    : CommonDialog(parent) {
    {
        Frame *F = pFrame = new Frame(this);
        F->setContentsMargins(0,0,0,0);

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
