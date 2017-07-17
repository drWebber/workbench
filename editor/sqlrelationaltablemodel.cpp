#include "sqlrelationaltablemodel.h"
#include <qdebug.h>

SqlRelationalTableModel::SqlRelationalTableModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{

}

void SqlRelationalTableModel::setRowsData(QModelIndex currentIndex, QVector<QVector<QString> > &table)
{
    int row = currentIndex.row();
    insertRows(row, table.size());
    foreach (QVector<QString> tableRow, table) {
        int col = currentIndex.column();
        foreach (QString value, tableRow) {
            setData(index(row, col), value);
            col++;
        }
        row++;
    }
}

void SqlRelationalTableModel::reselect()
{
    //сбрасываем модель, выполняем sql-запрос заново на индексы всех отображаемых значений
    QString tableName = this->tableName();
    QMap<int, QSqlRelation> relMap;
    for (int column = 0; column < columnCount(); ++column) {
        if (relation(column).isValid()) {
            relMap.insert(column, relation(column));
        }
    }
    clear();
    setTable(tableName);
    QMap<int, QSqlRelation>::iterator it = relMap.begin();
    while(it != relMap.end()){
        setRelation(it.key(), QSqlRelation(it.value()));
        ++it;
    }
    select();
}
