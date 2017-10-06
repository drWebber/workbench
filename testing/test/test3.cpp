#include "test3.h"
#include <qdebug.h>
#include <qsqlerror.h>
#include "store/store.h"
#include "store/newproduct.h"

Test3::Test3()
{
    qDebug() << "Test3 started";
    QStringList articles = QStringList() << "787211"
                                         << "787211"
                                         << "FAKE"
                                         << "4012"
                                         << "59703"
                                         << "59703"
                                         << "7761"
                                         << "7761"
                                         << "FAKE";

    QStringList descriptions = QStringList()
            << "Редукция лотка левая RKL 250/120B60-075"
            << "ЗАЩИТНАЯ НАКЛАДКА НА ДНИЩЕ ЛОТКА  W48 ПЛАСТИК"
            << "FAKE"
            << "Провод ПВС 5х4"
            << "Кабельный чулок с петлей,  д. 110-130 мм"
            << "БАЗОВЫЙ БЛОК SEPAM СЕРИИ 80 БЕЗ ДИСПЛЕЯ"
            << "Кабель КГВВнг(А)-LS 2х4(N) - 0,66"
            << "Саморезы универс. SG 4,5x45 желтый цинк (5500шт.)"
            << "FAKE";

    qDebug() << "Данные из NewProduct:";
    Store st(articles, descriptions);
    QList<NewProduct *> *products = st.getProducts();
    for (int i = 0; i < products->count(); ++i) {
        NewProduct *p = products->at(i);
        qDebug() << "pid" << p->getPid() << "art" << p->getArticle()
                 << "desc" << p->getDescription() << "mid" << p->getMid();
    }
    qDebug() << "Test3 finished";

}
