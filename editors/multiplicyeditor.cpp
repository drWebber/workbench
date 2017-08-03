#include "multiplicyeditor.h"
#include "ui_sqltablewin.h"

MultiplicyEditor::MultiplicyEditor(QString tableName, QWidget *parent):
    SqlTableWin(tableName, parent)
{
    setWindowTitle("Редактор кратности упаковки");
    ui->sqlTableView->setItemDelegateForColumn(0, new SqlInsDelegate("products", "pid", "art"));
    model->setRelation(0, QSqlRelation("products", "pid", "art"));
    model->select();
}

void MultiplicyEditor::hideColumns()
{

}
