#ifndef STORE_H
#define STORE_H
#include "newproduct.h"
#include "storeitem.h"
#include <qsqlquery.h>
#include <qsqlrecord.h>



class Store
{
public:
    Store(const QList<int> pids);
    Store(const QStringList articles, const int mid);
    Store(const QStringList articles, const QStringList descriptions);
    QList<NewProduct*> *getProducts() const;
private:
    void appendProduct(); // добавить пустой продукт
    void appendProduct(const QSqlRecord &rec);
    void appendProduct(const QVector<QString> &row);
    QList<NewProduct*> *products;
};

#endif // STORE_H
