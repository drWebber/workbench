#include "prodeditor.h"

ProdEditor::ProdEditor(QString tableName, QWidget *parent) : SqlTableWin(tableName, parent)
{
    setMinimumWidth(1024);
    setWindowTitle("Редактор продуктов");
    hideColumns();
    model->setRelation(5, QSqlRelation("manufacturers", "mid", "name"));
    model->select();
}

ProdEditor::ProdEditor(QString tableName, QStringList valsToInsert, QWidget *parent) :
    SqlTableWin(tableName, valsToInsert, parent)
{
    setMinimumWidth(1024);
    setWindowTitle("Редактор продуктов");
    hideColumns();
    model->setRelation(5, QSqlRelation("manufacturers", "mid", "name"));
    model->select();
    foreach (QString val, valsToInsert) {
        int newRow = model->rowCount();
        model->insertRow(newRow);
        model->setData(model->index(newRow, 1), QVariant(val));
    }
    ui->sqlTableView->scrollToBottom();
}

void ProdEditor::hideColumns()
{
    ui->sqlTableView->hideColumn(0);
}
