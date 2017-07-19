#include "prodeditor.h"

ProdEditor::ProdEditor(QString tableName, QWidget *parent) : SqlTableWin(tableName, parent)
{
    setMinimumWidth(1024);
    setWindowTitle("Редактор продуктов");
    hideColumns();
    model->setRelation(5, QSqlRelation("manufacturers", "mid", "name"));
    model->select();
}

void ProdEditor::hideColumns()
{
    ui->sqlTableView->hideColumn(0);
}
