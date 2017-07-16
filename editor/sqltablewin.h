#ifndef SQLTABLEWIN_H
#define SQLTABLEWIN_H

#include "delegates/sqlinsdelegate.h"
#include <qwidget.h>
#include <qsqlrelationaltablemodel.h>
#include <qsortfilterproxymodel.h>
#include <QSqlRelation>
#include <qtableview.h>
#include "sql/sqlquery.h"
#include "sqlrelationaltablemodel.h"

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
public slots:
    void slotAddRow();
    void slotDelRow();
private:
    Ui::SqlTableWin *ui;
    SqlRelationalTableModel *model;
    QSortFilterProxyModel *proxy;
    int editColumnNum = 0;
    SqlQuery sqe;
    QMenu *menu;
private slots:
    void onPasteActionTriggered();
    void onMenuRequested(QPoint pos);
    void onFirstRowEntered(QModelIndex indx);
    void on_pbnSave_clicked();
    void on_pbnRevert_clicked();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // SQLTABLEWIN_H
