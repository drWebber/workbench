#include "productvariety.h"

#include <qmessagebox.h>
#include <qdebug.h>

ProductVariety::ProductVariety(QList<QLineEdit *> lineEdits)
{
    this->lineEdits = lineEdits;
    query = new QSqlQuery();
}

QStringList ProductVariety::getFilter(const QString &key)
{
    QStringList pids;
    QString pidQuery = "SELECT pid FROM params WHERE kid = (SELECT kid FROM keywords WHERE name = '" + key + "')";
    for (int i = 1; i <= lineEdits.count(); ++i) {
        QString param = lineEdits[i-1]->text();
        if (!param.isEmpty()) {
            QString condition;
            if (param.contains(",")) {
                QStringList params = param.split(", ");
                QString range;
                foreach (QString val, params) {
                    range.append("'" + val + "', ");
                }
                range = range.left(range.length() - 2);
                condition = " IN(" + range + ")";
            } else {
                condition = " = '" + param + "'";
            }
            pidQuery.append(" AND param" + QString::number(i) + condition);
        }
    }
//    qDebug() << pidQuery;
    query->exec(pidQuery);
    while (query->next()) {
        pids.append(query->value(0).toString());
    }
    return pids;
}
