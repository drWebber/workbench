#include "manufacturerseditor.h"

#include <qtextcodec.h>

ManufacturersEditor::ManufacturersEditor(QString tableName, QWidget *parent) : SqlTableWin(tableName, parent)
{
    setWindowTitle("Редактор производителей");
    hideColumns();
    model->select();
}

void ManufacturersEditor::hideColumns()
{
    ui->sqlTableView->hideColumn(0);
}
