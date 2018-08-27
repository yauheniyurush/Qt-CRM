#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace CRM {

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QAction *closeAction;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

} //namespace CRM

#endif // MAINWINDOW_H
