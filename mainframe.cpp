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

    clients::TableView *M = new clients::TableView(this);
    L->addWidget(M);

    L->setContentsMargins(3,3,3,3);
    L->setStretchFactor(M,5);
    L->setStretchFactor(frame,1);


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

void mainframe::apply_filter_triggered(){
    emit apply_filter(this);
}

} //namespace CRM
