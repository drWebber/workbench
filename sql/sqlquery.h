#ifndef SQLQUERY_H
#define SQLQUERY_H
#include <qsqlquery.h>
#include <qvariant.h>

class SqlQuery
{
public:
    SqlQuery();
    QVariant getSingleVal(QString query);
    QVector<QString> getSingleVals(QString query);
    QStringList getSingleValsList(QString query);
    static QString argListToLine(const QList<int> &list);
    static QString argListToLine(const QStringList &list);
private:
    QSqlQuery *sqlquery;
};

#endif // SQLQUERY_H
