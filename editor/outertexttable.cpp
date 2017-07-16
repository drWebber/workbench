#include "outertexttable.h"
#include <qdebug.h>

OuterTextTable::OuterTextTable(QVector<QVector<QString> > outerTextTabe, SqlRelationalTableModel *model)
{
    table = outerTextTabe;
    this->model = model;
}

void OuterTextTable::printTable()
{
    foreach (QVector<QString> vector, table) {
        QString output;
        foreach (QString val, vector) {
            output.append(val + " ");
        }
        qDebug() << output;
    }
}
