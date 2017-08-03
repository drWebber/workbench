#include "parameditor.h"
#include "delegates/sqlinsdelegate.h"

ParamEditor::ParamEditor(QString tableName, QWidget *parent) :
    SqlTableWin(tableName, parent)
{
    setWindowTitle("Редактор параметров");
    setMinimumWidth(1042);

    SqlInsDelegate *keywordsDelegate = new SqlInsDelegate("keywords", "kid", "name");
    ui->sqlTableView->setItemDelegateForColumn(0, keywordsDelegate);
    SqlInsDelegate *productsDelegate = new SqlInsDelegate("products", "pid", "art");
    ui->sqlTableView->setItemDelegateForColumn(1, productsDelegate);

    model->setRelation(0, QSqlRelation("keywords", "kid", "name"));
    model->setRelation(1, QSqlRelation("products", "pid", "art"));

    model->select();

    connect(ui->sqlTableView->model(),SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
            this, SLOT(onFirstRowEntered(QModelIndex)));

}

void ParamEditor::hideColumns()
{

}
