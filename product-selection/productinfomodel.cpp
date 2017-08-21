#include "productinfomodel.h"
#include <qsqlerror.h>

#include <qdebug.h>

ProductInfoModel::ProductInfoModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

int ProductInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return products.count();
}

int ProductInfoModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Product::LAST;
}

QVariant ProductInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole &&
                            role != Qt::EditRole)) {
        return QVariant();
    }
    return products[index.row()][Product::Column(index.column())];
}

QVariant ProductInfoModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return ++section;
    }
    switch (section) {
    case Product::PRODUCT_ID:
        return "Pid";
    case Product::ARTICLE:
        return "Артикул";
    case Product::DESCRIPTION:
        return "Наименование";
    case Product::VIT_STORE:
        return "Витебск";
    case Product::MINSK_STORE:
        return "Минск";
    case Product::OUTER_STORE:
        return "Прочие";
    case Product::PRICE:
        return "База";
    }
    return QVariant();
}

bool ProductInfoModel::selectProducts(const QStringList &pids)
{
    resetModel();

    if (pids.isEmpty()) return false;

    //для листа продуктов цикл обхода построчно вместо while ниже
    Product prod = Product(pids);
    foreach (Item product, prod.getProducts()) {
        int row = products.count();
        beginInsertRows(QModelIndex(), row, row);
        products.append(product);
        endInsertRows();
    }
    return true;
}

void ProductInfoModel::resetModel()
{
    beginResetModel();
    products.clear();
    endResetModel();
}
