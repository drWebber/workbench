#ifndef MANUFACTURERSEDITOR_H
#define MANUFACTURERSEDITOR_H

#include "sqltablewin.h"
#include <ui_sqltablewin.h>

class ManufacturersEditor : public SqlTableWin
{
public:
    ManufacturersEditor(QString tableName, QWidget *parent = 0);

    // SqlTableWin interface
public:
    void hideColumns() override;
};

#endif // MANUFACTURERSEDITOR_H
