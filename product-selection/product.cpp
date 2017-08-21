#include "product.h"
#include <qsqlerror.h>

#include <qdebug.h>

Product::Product(const QStringList &pids)
{
    this->pids = pids;
}

QList<QHash<Product::Column, QVariant>> Product::getProducts()
{
    QList<Item> products;

    QString str = "SELECT `pid`, `art`, `description`, `mid` "
                  "FROM `products` "
                  "WHERE pid IN(" + getPidsRange() + ")";
    QSqlQuery query(str);
    if (!query.exec()) {
        return products;
    }
    while (query.next()) {
        products.append(getProduct(query));
    }

    return products;
}

QString Product::getPidsRange()
{
    QString range;
    foreach (QString pid, pids) {
        range.append(pid + ", ");
    }
    return range.left(range.length() - 2);
}

QString Product::getStoreRemainings(const QString &pid,
                                    const QString &mid,
                                    const QString &store)
{
    QString smid = getSmid(mid, store);
    if (smid.isEmpty()) {
        return QString("незвестно");
    }
    QSqlQuery query;
    query.prepare("SELECT `count` "
                  "FROM `store` "
                  "WHERE `pid` = :pid AND `smid` = :smid");
    query.bindValue(":pid", pid);
    query.bindValue(":smid", smid);
    if (!query.exec() | !query.next()) {
        return QString();
    }
    return query.value(0).toString();
}

QString Product::getSmid(const QString &mid,
                         const QString &store)
{
    QSqlQuery query;
    query.prepare("SELECT `smid` "
                  "FROM `store_manufacturer` "
                  "WHERE `mid` = :mid AND `storePlace` = :storePlace");
    query.bindValue(":mid", mid);
    query.bindValue(":storePlace", store);
    if (!query.exec() | !query.next()) {
        return QString();
    }
    return query.value(0).toString();
}

QHash<Product::Column, QVariant> Product::getProduct(const QSqlQuery &query)
{
    Item prod;
    QString pid = query.value("pid").toString();
    QString mid = query.value("mid").toString();
    prod.insert(PRODUCT_ID, pid);
    prod.insert(ARTICLE, query.value("art"));
    prod.insert(DESCRIPTION, query.value("description"));
    prod.insert(VIT_STORE, getStoreRemainings(pid, mid, "Витебск"));
    prod.insert(MINSK_STORE, getStoreRemainings(pid, mid, "Минск"));
    prod.insert(OUTER_STORE, getStoreRemainings(pid, mid, "Внешние"));

    return prod;
}
