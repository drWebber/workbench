#include "keywordseditor.h"
#include <qdebug.h>

KeywordsEditor::KeywordsEditor(QString tableName, QWidget *parent) :
    SqlTableWin(tableName, parent)
{
    hideColumns();
}

void KeywordsEditor::hideColumns()
{
    ui->sqlTableView->hideColumn(0);
}
