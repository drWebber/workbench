#ifndef MULTIPLICYEDITOR_H
#define MULTIPLICYEDITOR_H

#include "sqltablewin.h"

class MultiplicyEditor : public SqlTableWin
{
public:
    MultiplicyEditor(QString tableName, QWidget *parent = 0);
public:
    void hideColumns();
};

#endif // MULTIPLICYEDITOR_H
