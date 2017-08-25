#include "productvariety.h"

#include <qdebug.h>
#include <qmessagebox.h>

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
    qDebug() << pidQuery;
    query->exec(pidQuery);
    while (query->next()) {
        pids.append(query->value(0).toString());
    }
    return pids;
}

QVector<QStringList> ProductVariety::getStoreRemainings(const QList<int> &pids, const QList<int> &mids)
{
    QVector<QStringList> remainings;

    if(pids.count() != mids.count()){
        QMessageBox::critical(NULL, "Ошибка", "QVector<QStringList> ProductVariety::getStoreRemainings pids.count() != mids.count()");
        return remainings;
    }

    for (int i = 0; i < pids.count(); ++i) {
        remainings.append(getItemRemainings(pids[i], mids[i]));
    }
    return remainings;
}

QStringList ProductVariety::getItemRemainings(const int &pid, const int &mid)
{
    QStringList stores, itemRemainings;
    stores << "Витебск" << "Минск" << "Внешнее";
    foreach (QString store, stores) {
        query->prepare("SELECT `count` FROM `store` WHERE pid = :pid AND smid = "
                       "(SELECT `smid` FROM `store_manufacturer` WHERE mid = :mid AND `storePlace` = :place)");
        query->bindValue(":pid", pid);
        query->bindValue(":mid", mid);
        query->bindValue(":place", store);
        query->exec();
        if (query->next()){
            itemRemainings.append(query->value(0).toString());
        } else {
            itemRemainings.append("unknown");
        }
    }
    return itemRemainings;
}
