#ifndef PRODEDITOR_H
#define PRODEDITOR_H

#include "sqltablewin.h"
#include <ui_sqltablewin.h>

class ProdEditor : public SqlTableWin
{
public:
    ProdEditor(QString tableName, QWidget *parent = 0);
    ProdEditor(QString tableName, QStringList valsToInsert, QWidget *parent = 0);

    // SqlTableWin interface
public:
    void hideColumns() override;
};

#endif // PRODEDITOR_H
