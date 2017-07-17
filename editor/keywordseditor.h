#ifndef KEYWORDSEDITOR_H
#define KEYWORDSEDITOR_H

#include "sqltablewin.h"
#include <ui_sqltablewin.h>

class KeywordsEditor : public SqlTableWin
{
public:
    KeywordsEditor(QString tableName, QWidget *parent = 0);

    // SqlTableWin interface
public:
    void hideColumns() override;
};

#endif // KEYWORDSEDITOR_H
