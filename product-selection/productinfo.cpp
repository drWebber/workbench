#include "productinfo.h"

ProductInfo::ProductInfo(QStandardItemModel *model)
{
    this->model = model;
}

void ProductInfo::setRemainingsData(const QVector<QStringList> &remainings)
{
    removeAllRows();
    for (int i = 0; i < remainings.count(); ++i) {
        model->insertRow(i);
        for (int j = 0; j < remainings[i].count(); ++j) {
            model->setData(model->index(i, j), remainings[i][j]);
        }
    }
}

void ProductInfo::removeAllRows()
{
    model->removeRows(0, model->rowCount());
}
