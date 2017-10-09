#ifndef STORE_H
#define STORE_H
#include "store/newproduct.h"
#include "storeitem.h"
#include <qlist.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>

class Store
{
public:
    Store(QList<int> *pids);
    Store(const QStringList articles, const int mid);
    Store(const QStringList articles, const QStringList descriptions);
    QList<NewProduct*> *getProducts() const;
    QList<StoreItem *> *getStoreItems() const;
    QString getStoreBalance(int pid, int smid);
private:
    void appendProduct(); // добавить пустой продукт
    void appendProduct(const QSqlRecord &rec);
    void appendProduct(const QVector<QString> &row);
    QList<NewProduct *> *products;
    QList<StoreItem *> *storeItems;
};

#endif // STORE_H
