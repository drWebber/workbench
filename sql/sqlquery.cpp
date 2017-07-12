#include "sql/sqlquery.h"
#include <qsqlquery.h>
#include <qsql.h>
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
