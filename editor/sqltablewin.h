#ifndef SQLTABLEWIN_H
#define SQLTABLEWIN_H

#include "delegates/sqlinsdelegate.h"
#include <qsqlrelationaltablemodel.h>
#include <qsortfilterproxymodel.h>
#include <QSqlRelation>
#include <qtableview.h>
#include "sql/sqlquery.h"
#include "sqlrelationaltablemodel.h"
#include <qdialog.h>

namespace Ui {
    class SqlTableWin;
}

class SqlTableWin : public QDialog
{
    Q_OBJECT

public:
    SqlTableWin(QString tableName, QWidget *parent = 0);
    SqlTableWin(QString tableName, QStringList valsToInsert, QWidget *parent = 0);
    SqlTableWin(QString tableName, int column,
                QVector<QVector<QString> > tableToInsert, QWidget *parent = 0);
    ~SqlTableWin();
    virtual void hideColumns() = 0;
    void keyPressEvent(QKeyEvent *e);
protected:
    SqlRelationalTableModel *model;
    QSortFilterProxyModel *proxy;
    SqlQuery sqe;
    QMenu *menu;
protected slots:
    void slotAddRow();
    void slotDelRow();
    void onPasteActionTriggered();
    void onMenuRequested(QPoint pos);
    void onFirstRowEntered(QModelIndex indx);
    void on_pbnSave_clicked();
    void on_pbnRevert_clicked();
    // QWidget interface
protected:
    Ui::SqlTableWin *ui;
    void closeEvent(QCloseEvent *event) override;
private:
    void setUp(QString tableName);
};

#endif // SQLTABLEWIN_H
