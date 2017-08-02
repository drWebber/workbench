#include "keywordseditor.h"
#include <qdebug.h>

KeywordsEditor::KeywordsEditor(QString tableName, QWidget *parent) :
    SqlTableWin(tableName, parent)
{
    setWindowTitle("Редактор ключевых слов");
    hideColumns();
    model->select();
}

KeywordsEditor::KeywordsEditor(QString tableName, QStringList valsToInsert, QWidget *parent) :
    SqlTableWin(tableName, valsToInsert, parent)
{
    setWindowTitle("Редактор ключевых слов");
    hideColumns();
    model->select();
    foreach (QString val, valsToInsert) {
        int newRow = model->rowCount();
        model->insertRow(newRow);
        model->setData(model->index(newRow, 1), QVariant(val));
    }
    ui->sqlTableView->scrollToBottom();
}

void KeywordsEditor::hideColumns()
{
    ui->sqlTableView->hideColumn(0);
}
