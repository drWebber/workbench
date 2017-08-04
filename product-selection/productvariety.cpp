#include "productvariety.h"

#include <qdebug.h>

ProductVariety::ProductVariety(QList<QLineEdit *> lineEdits)
{
    this->lineEdits = lineEdits;
    query = new QSqlQuery();
}

QString ProductVariety::getFilter(const QString &key, const int &sender)
{
    pids.clear();
    query->prepare("SELECT kid FROM keywords WHERE name = :name");
    query->bindValue(":name", key);
    query->exec();
    if (!query->next()) return QString();

    QString kid = query->value(0).toString();
    QString pidQuery = "SELECT pid FROM params WHERE kid = '" + kid + "'";
    for (int i = 1; i <= sender; ++i) {
        QString param = lineEdits[i-1]->text();
        if (!param.isEmpty()) {
            pidQuery.append(" AND param" + QString::number(i) +
                            " = '" + param + "'");
        }
    }

    query->exec(pidQuery);
    while (query->next()) {
        pids.append(query->value(0).toString());
    }

    QString where = "pid IN (";
    foreach (QString pid, pids) {
        where.append("'" + pid + "', ");
    }
    where = where.left(where.size()-2);
    where.append(")");

    return where;
}
