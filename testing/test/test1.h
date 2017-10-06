#ifndef TEST1_H
#define TEST1_H

#include <qsqlquerymodel.h>
#include "product-selection/productinfomodel.h"

class Test1
{
public:
    Test1();
    QSqlQueryModel *getSourceModel() const;
    ProductInfoModel *getResultModel() const;
private:
    QSqlQueryModel *sourceModel;
    ProductInfoModel *resultModel;
};

#endif // TEST1_H
