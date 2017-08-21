#ifndef PRODUCT_H
#define PRODUCT_H

#include <qhash.h>
#include <qvariant.h>
#include <qsqlquery.h>

class Product
{
public:
    Product(const QStringList &pids);
    enum Column{
        PRODUCT_ID, ARTICLE, DESCRIPTION, VIT_STORE, MINSK_STORE,
        OUTER_STORE, PRICE, LAST
    };
    QList<QHash<Column, QVariant> > getProducts();
private:
    QStringList pids;
    typedef QHash<Column, QVariant> Item;
    QString getPidsRange();
    QString getStoreRemainings(const QString &pid,
                               const QString &mid,
                               const QString &store);
    QString getSmid(const QString &mid,
                    const QString &store);
    QHash<Column, QVariant> getProduct(const QSqlQuery &query);
};

#endif // PRODUCT_H
