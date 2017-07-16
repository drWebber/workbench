#ifndef OUTERTEXTTABLE_H
#define OUTERTEXTTABLE_H

#include "sqlrelationaltablemodel.h"
#include <qvector.h>

class OuterTextTable
{
public:
    OuterTextTable(QVector<QVector<QString>> outerTextTabe, SqlRelationalTableModel* model);
    void printTable();
    void replaceDisplayDataToIndex();


private:
    QVector<QVector<QString>> table;
    SqlRelationalTableModel* model;
};

#endif // OUTERTEXTTABLE_H
