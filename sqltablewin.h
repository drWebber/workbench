#ifndef SQLTABLEWIN_H
#define SQLTABLEWIN_H

#include "delegates/sqlinsdelegate.h"
#include <qwidget.h>
#include <qsqlrelationaltablemodel.h>
#include <QSqlRelation>
#include <qtableview.h>
#include "sql/sqlquery.h"

namespace Ui {
class SqlTableWin;
}

class SqlTableWin : public QWidget
{
    Q_OBJECT

public:
    explicit SqlTableWin(QString mainSqlTable, QWidget *parent = 0);
    explicit SqlTableWin();
    ~SqlTableWin();
    void setRelation(int col, QSqlRelation rel);
    void setDelegate(int col, SqlInsDelegate *delegate);
    void hideCol(int col);
    void setEditColumn(int col);
    void keyPressEvent(QKeyEvent *e);
    void connectFirstColEnteredSignal();
private:
    Ui::SqlTableWin *ui;
    QSqlRelationalTableModel *model;
    int editColumnNum = 0;
    SqlQuery sqe;
public slots:
    void slotAddRow();
    void slotDelRow();
    void slotMenuRequested(QPoint pos);
    void slotFirstRowEntered(QModelIndex indx);
};

#endif // SQLTABLEWIN_H
