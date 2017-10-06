#include "test1.h"

#include "sql/sqlquery.h"
#include "store/store.h"
#include "store/newproduct.h"

Test1::Test1()
{
    QList<int> source_pids = QList<int>() << 1 << 99 << 180 << 516 << 1000 << 1048 << 22;
    sourceModel = new QSqlQueryModel();
    sourceModel->setQuery("SELECT * FROM `products` WHERE pid IN(" +
                         SqlQuery::argListToLine(source_pids) + ")");


    resultModel = new ProductInfoModel();
    QStringList result_pids;
    Store st(&source_pids);
    QList<NewProduct *> *products = st.getProducts();
    for (int i = 0; i < products->count(); ++i) {
        NewProduct *prod = products->at(i);
        result_pids.append(QString::number(prod->getPid()));
    }
    resultModel->selectProducts(result_pids);
}

ProductInfoModel *Test1::getResultModel() const
{
    return resultModel;
}

QSqlQueryModel *Test1::getSourceModel() const
{
    return sourceModel;
}
