#ifndef PATTEDITOR_H
#define PATTEDITOR_H

#include "sqltablewin.h"
#include <ui_sqltablewin.h>

class PattEditor : public SqlTableWin
{
public:
    PattEditor(QString tableName, QWidget *parent = 0);

    // SqlTableWin interface
public:
    void hideColumns() override;
};

#endif // PATTEDITOR_H
