#include "mainframe.h"
#include "clients.h"

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


}

} //namespace CRM
