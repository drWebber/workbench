#include "patteditor.h"

PattEditor::PattEditor(QString tableName, QWidget *parent) : SqlTableWin(tableName, parent)
{
    setWindowTitle("Редактор шаблонов");
    ui->sqlTableView->setItemDelegateForColumn(0, new SqlInsDelegate("keywords", "kid", "name"));
    model->setRelation(0, QSqlRelation("keywords", "kid", "name"));
    model->select();
}

void PattEditor::hideColumns()
{

}
