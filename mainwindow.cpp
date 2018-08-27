#include "mainwindow.h"

#include <QMenuBar>

namespace CRM {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    {
        QAction *A = closeAction = new QAction( this ) ;
        A->setText(tr("Close"));
        connect(closeAction, SIGNAL(triggered()), this, SLOT(close())) ;
    }

    QMenu *mItem = menuBar()->addMenu(tr("File"));
    mItem->addAction(closeAction);
}

MainWindow::~MainWindow()
{

}

}//namespace CRM
