#ifndef OUTERTEXTTABLE_H
#define OUTERTEXTTABLE_H

#include "sqlrelationaltablemodel.h"
#include <qvector.h>
#include <qmap.h>

class OuterTextTable
{
public:
    OuterTextTable(QVector<QVector<QString>> outerTextTabe, SqlRelationalTableModel* model);
    void printTable();
    void replaceDisplayDataToIndex();
    QVector<QVector<QString> > getTable() const;

private:
    QVector<QVector<QString>> table;
    SqlRelationalTableModel* model;
    QString getIndexValue(QString displayVal, int col);
    QMap<int, QVector<int>> preInsert;
};

#endif // OUTERTEXTTABLE_H
