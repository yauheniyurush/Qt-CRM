#include "mainframe.h"
#include "clients.h"
#include <QDebug>

namespace CRM {

mainframe::mainframe(QWidget *parent)
    :QFrame(parent) {

    setFrameStyle(StyledPanel | Sunken);
    setSizePolicy(QSizePolicy::Expanding,
                  QSizePolicy::Expanding);

    QVBoxLayout *L = new QVBoxLayout(this);

    QFrame *frame = new QFrame(this);
    ui.setupUi(frame);

    L->addWidget(frame);

    clients::TableView *M = new clients::TableView(this) ;
    M->setSizePolicy(QSizePolicy::Expanding,
                     QSizePolicy::Expanding);
    L->addWidget(M);

    L->setContentsMargins(3,0,3,0);
    //L->setStretchFactor(M,8);
    //L->setStretchFactor(frame,1);


    //фильтер
    ui.toolButton->setDefaultAction(ui.actionApplyFilter);
    connect(ui.actionApplyFilter,SIGNAL(triggered()),
            this,SLOT(apply_filter_triggered()));
    //сигнал фильтра
    connect(this,SIGNAL(apply_filter(QObject*)),
            M->model(),SLOT(apply_filter(QObject*)));

}


QVariant mainframe::name() const {
    QString T = ui.nameEdt->text().simplified();
    return T.isEmpty() ? QVariant() : T;
}

QVariant mainframe::surname() const {
    QString T = ui.surnameEdt->text().simplified();
    return T.isEmpty() ? QVariant() : T;
}

QVariant mainframe::Patronymic() const {
    QString T = ui.EdtPatronymic->text().simplified();
    return T.isEmpty() ? QVariant() : T;
}

QVariant mainframe::City() const {
    QString T = ui.edtCity->text().simplified();
    return T.isEmpty() ? QVariant() : T;
}

QVariant mainframe::Street() const {
    QString T = ui.edtStreet->text().simplified();
    return T.isEmpty() ? QVariant() : T;
}

QVariant mainframe::PhoneNumber() const {
    QString T = ui.EdtPhone->text().simplified();
    return T.isEmpty() ? QVariant() : T;
}


void mainframe::apply_filter_triggered(){
    emit apply_filter(this);
}

} //namespace CRM
