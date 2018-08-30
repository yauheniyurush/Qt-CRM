#ifndef POSACTION_H
#define POSACTION_H

#include <QAction>
#include <QModelIndex>

namespace CRM {

class PosAction : public QAction
{
    Q_OBJECT
public:
    QModelIndex I ;
    QWidget *pWidget;
public:
    PosAction( QObject *parent = 0);
    virtual ~PosAction(){}
private slots:
    void was_triggered();
signals:
    void editItem(const QModelIndex &I, QWidget *parent);
};

}//namespace CRM

#endif // POSACTION_H
