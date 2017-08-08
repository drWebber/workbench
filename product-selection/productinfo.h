#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include <qvector.h>
#include <qstandarditemmodel.h>

class ProductInfo
{
public:
    ProductInfo(QStandardItemModel *model);
    void setRemainingsData(const QVector<QStringList> &remainings);
    void removeAllRows();
private:
    QStandardItemModel *model;
};

#endif // PRODUCTINFO_H
