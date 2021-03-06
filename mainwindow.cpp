#include "mainwindow.h"
#include "mainframe.h"
#include "clients.h"

#include <QMenuBar>

namespace CRM {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    {
        QAction *A = closeAction = new QAction( this ) ;
        A->setText(tr("Выход"));
        connect(closeAction, SIGNAL(triggered()), this, SLOT(close())) ;
    }

    QMenu *mItem = menuBar()->addMenu(tr("Файл"));
    mItem->addAction(closeAction);

    mainframe *M = new mainframe(this);
    setCentralWidget(M);


}

MainWindow::~MainWindow()
{

}

}//namespace CRM
