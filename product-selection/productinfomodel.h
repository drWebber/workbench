#ifndef PRODUCTINFOMODEL_H
#define PRODUCTINFOMODEL_H

#include <qabstractitemmodel.h>
#include <qsqlquery.h>

class ProductInfoModel : public QAbstractTableModel
{
public:
    explicit ProductInfoModel(QObject *parent = 0);
private:
    enum Column{
        PRODUCT_ID, ARTICLE, DESCRIPTION, VIT_STORE, MINSK_STORE,
        OUTRE_STORE, PRICE, LAST
    };
    typedef QHash<Column, QVariant> Product;
    typedef QList<Product> Products;
    Products products;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool selectProducts(const QStringList &pids);
};

#endif // PRODUCTINFOMODEL_H
