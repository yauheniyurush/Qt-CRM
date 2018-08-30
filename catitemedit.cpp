#include "catitemedit.h"

#include <QtSql>

namespace CRM {
namespace Catalogue {
namespace Item {

/*************************************************************/

Data::Data(QObject *parent, QSqlQuery &qry)
    : QObject(parent) {

    Id      = qry.value("iid"       ) ;
    Code    = qry.value("code"      ).toString() ;
    Title   = qry.value("Title"     ).toString() ;
    From    = qry.value("valid_from").toDateTime() ;
    To      = qry.value("valid_to"  ).toDateTime() ;
    IsLocal = qry.value("is_local"  ).toBool() ;
    Comment = qry.value("acomment"   ).toString() ;
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
    ui.edtCode->setText(Block->Code);
    ui.edtTitle->setText(Block->Title);
    ui.cbxLocal->setChecked(Block->IsLocal);
    ui.edtComment->setText(Block->Comment);
    ui.cbxFromEnabled->setChecked(Block->From.isValid());
    ui.edtFrom->setDateTime(Block->From);
    ui.cbxToEnabled->setChecked(Block->To.isValid());
    ui.edtTo->setDateTime(Block->To);
}

bool Frame::save() {
    if (!Block) return false;


    Block->Code = ui.edtCode->text().simplified();
    Block->Title = ui.edtTitle->text().simplified();
    Block->IsLocal = ui.cbxLocal->isChecked();
    Block->Comment = ui.edtComment->toPlainText().trimmed();
    if (ui.cbxFromEnabled->isChecked()){
        Block->From = ui.edtFrom->dateTime();
    }
    else {
        Block->From = QDateTime();
    }
    if (ui.cbxToEnabled->isChecked()){
        Block->To = ui.edtTo->dateTime();
    }
    else {
        Block->To = QDateTime();
    }
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
    if (!From.isValid()) {
        if (From > QDateTime:: currentDateTime())
        return false;
    }
    if (To.isValid()) {
        if (To<QDateTime::currentDateTime()) return false;
    }
    return true;
}

}//namespace Item
}//namespace Catalogue
}//namespace CRM
