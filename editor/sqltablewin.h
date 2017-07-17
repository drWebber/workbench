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
    explicit SqlTableWin(QString tableName, QWidget *parent = 0);
    ~SqlTableWin();
    void setRelation(int col, QSqlRelation rel);
    void setDelegate(int col, SqlInsDelegate *delegate);
    void hideCol(int col);
    virtual void hideColumns();
    void setEditColumn(int col);
    void keyPressEvent(QKeyEvent *e);
    void connectFirstColEnteredSignal();
public slots:
    void slotAddRow();
    void slotDelRow();
private:
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
    Ui::SqlTableWin *ui;
    void closeEvent(QCloseEvent *event) override;
};

#endif // SQLTABLEWIN_H
