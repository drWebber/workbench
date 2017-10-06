#include "sql/sqlquery.h"
#include <qsqlquery.h>
#include <QSqlRecord>
#include <QVector>
#include <qdebug.h>

SqlQuery::SqlQuery()
{
    this->sqlquery = new QSqlQuery();
}

QVariant SqlQuery::getSingleVal(QString query)
{
    sqlquery->clear();
    sqlquery->exec(query);
    sqlquery->next();
    return sqlquery->value(0);
}

QVector<QString> SqlQuery::getSingleVals(QString query)
{
    QVector<QString> vector;
    sqlquery->clear();
    sqlquery->exec(query);
    while(sqlquery->next()){
        vector.append(sqlquery->value(0).toString());
    }
    return vector;
}

QStringList SqlQuery::getSingleValsList(QString query)
{
    QStringList list;
    sqlquery->clear();
    sqlquery->exec(query);
    while(sqlquery->next()){
        list.append(sqlquery->value(0).toString());
    }
    return list;
}

QString SqlQuery::argListToLine(const QList<int> &list)
{
    QString result;
    QListIterator<int> it(list);
    while (it.hasNext()) {
        result.append('"' + QString::number(it.next()) + "\",");
    }
    result.chop(1);
    return result;
}

QString SqlQuery::argListToLine(const QStringList &list)
{
    QString result;
    QListIterator<QString> it(list);
    while (it.hasNext()) {
        result.append('"' + it.next() + "\",");
    }
    result.chop(1);
    return result;
}
