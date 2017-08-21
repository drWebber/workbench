#ifndef PRODUCTINFOMODEL_H
#define PRODUCTINFOMODEL_H

#include <qabstractitemmodel.h>
#include <qsqlquery.h>
#include "product-selection/product.h"

class ProductInfoModel : public QAbstractTableModel
{
public:
    explicit ProductInfoModel(QObject *parent = 0);
private:
    typedef QHash<Product::Column, QVariant> Item;
    typedef QList<Item> Products;
    Products products;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool selectProducts(const QStringList &pids);
    void resetModel();
};

#endif // PRODUCTINFOMODEL_H
