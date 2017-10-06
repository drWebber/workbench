#include "test2.h"
#include <qdebug.h>
#include <qsqlerror.h>
#define DKC_MID 4

Test2::Test2()
{
    qDebug() << "Test2 started";
    qDebug() << "Данные из sql запроса:";
    QStringList articles = QStringList() << "35522" << "BBC3010" << "35022"
                                         << "BPL2930" << "R5MP01"
                                         << "WRONG1"
                                         << "BPM2920";
    QSqlQuery q;
    q.exec("SELECT * FROM `products` WHERE `art` IN(" +
           SqlQuery::argListToLine(articles) + ") AND mid = "
           + QString::number(DKC_MID));
    while (q.next()) {
        qDebug() << "pid"  << q.value(0).toString()
                 << "art"  << q.value(1).toString()
                 << "desc" << q.value(2).toString()
                 << "mid"  << q.value(3).toString();
    }

    qDebug() << "Данные из NewProduct:";
    Store st(articles, DKC_MID);
    QList<NewProduct *> *products = st.getProducts();
    for (int i = 0; i < products->count(); ++i) {
        NewProduct *p = products->at(i);
        qDebug() << "pid" << p->getPid() << "art" << p->getArticle()
                 << "desc" << p->getDescription() << "mid" << p->getMid();
    }
    qDebug() << "Test2 finished";
}
