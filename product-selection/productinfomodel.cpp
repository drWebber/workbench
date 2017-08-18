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
    return LAST;
}

QVariant ProductInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole &&
                            role != Qt::EditRole)) {
        return QVariant();
    }
    return products[index.row()][Column(index.column())];
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
    case PRODUCT_ID:
        return "Pid";
    case ARTICLE:
        return "Артикул";
    case DESCRIPTION:
        return "Наименование";
    case VIT_STORE:
        return "Витебск";
    case MINSK_STORE:
        return "Минск";
    case OUTRE_STORE:
        return "Прочие";
    case PRICE:
        return "База";
    }
    return QVariant();
}

bool ProductInfoModel::selectProducts(const QStringList &pids)
{
    СОЗДАТЬ ОТДЕЛЬНЫЙ МЕТОД ПОДГОТОВКИ ПРЕДИКАТА IN
    QString str = "SELECT `pid`, `art`, `description`"
                  "FROM `products`";
    if (pids.count() > 0) {
        str.append(" WHERE pids IN(");
    }
    foreach (QString pid, pids) {
        str.append(pid + ", ");
    }
    QSqlQuery query(str);
    if (!query.exec()) {
        qDebug() << "Ошибка query.exec() ProductInfoModel::setQuery()";
        qDebug() << query.lastError();
        qDebug() << query.lastQuery();
        return false;
    }
    while (query.next()) {
        int row = products.count();
        Product prod;
        prod.insert(PRODUCT_ID, query.value("pid"));
        prod.insert(ARTICLE, query.value("art"));
        prod.insert(DESCRIPTION, query.value("description"));
        beginInsertRows(QModelIndex(), row, row);
        products.append(prod);
        endInsertRows();
    }
    return true;
}
