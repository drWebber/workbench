#include "keywordseditor.h"
#include <qdebug.h>

KeywordsEditor::KeywordsEditor(QString tableName, QWidget *parent) :
    SqlTableWin(tableName, parent)
{
    setWindowTitle("Редактор ключевых слов");
    hideColumns();
    model->select();
}

void KeywordsEditor::hideColumns()
{
    ui->sqlTableView->hideColumn(0);
}
