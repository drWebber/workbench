#ifndef SQLRELATIONALTABLEMODEL_H
#define SQLRELATIONALTABLEMODEL_H

#include <qsqlrelationaltablemodel.h>
#include <qobject.h>
#include <qsqldatabase.h>

class SqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    SqlRelationalTableModel(QObject *parent);
    void setRowsData(QModelIndex currentIndex, QVector<QVector<QString> > &table);
    void reselect();
};

#endif // SQLRELATIONALTABLEMODEL_H
