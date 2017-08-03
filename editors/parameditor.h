#ifndef PARAMEDITOR_H
#define PARAMEDITOR_H

#include "sqltablewin.h"
#include "ui_sqltablewin.h"

class ParamEditor : public SqlTableWin
{
public:
    ParamEditor(QString tableName, QWidget *parent = 0);

    // SqlTableWin interface
public:
    void hideColumns() override;
};

#endif // PARAMEDITOR_H
