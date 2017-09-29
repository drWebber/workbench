#include "store.h"
#include "storeitem.h"
#include "sql/sqlquery.h"
#include <qvector.h>

Store::Store(const QList<int> pids)
{
    QSqlQuery q;
    q.exec("SELECT * FROM `products` WHERE `pid` IN("
           + SqlQuery::argListToLine(pids) + ")");
    while (q.next()) {
        appendProduct(q.record());
    }
}

Store::Store(const QStringList articles, const int mid)
{
    QSqlQuery q;
    q.exec("SELECT * FROM `products` WHERE `articles` IN("
           + SqlQuery::argListToLine(articles) +
           ") AND mid='" + QString::number(mid) + "')");
    while (q.next()) {
        appendProduct(q.record());
    }
}

Store::Store(const QStringList articles, const QStringList descriptions)
{
    // Проблема: под одним артикулом может быть несоклько товаров
    // Собираем все вариации доступных артикулов и описаний, далее идентифицируем
    // записи дополнительно по описанию
    QSqlQuery q;
    q.exec("SELECT * FROM `products` WHERE `art` IN("
           + SqlQuery::argListToLine(articles) +
           ")");

    // Получаем вектор векторов со всеми возможными совпаденями артикулов
    QVector<QVector<QString> > dirtyRes;
    while (q.next()) {
        QVector<QString> tmp;
        tmp.append(q.value("pid").toString());
        tmp.append(q.value("art").toString());
        tmp.append(q.value("description").toString());
        tmp.append(q.value("mid").toString());
        tmp.append(q.value("main_unit").toString());
        tmp.append(q.value("main_mult").toString());
        tmp.append(q.value("sec_unit").toString());
        tmp.append(q.value("sec_mult").toString());
        dirtyRes.append(tmp);
    }

    // Ищем искомый артикул, если он один - pid наш,
    // если не один - дополнительно сверяем описание продукта
    for (int i = 0; i < articles.count(); ++i) {
        QString currtArt = articles.at(i);
        QList<int> dirtyIndexes;
        // ищем в dirtyRes записи с артикулами
        for (int x = 0; x < dirtyRes.count(); ++x) {
            QVector<QString> currRec = dirtyRes.at(x);
            if (currRec.at(0) == currtArt) {
                dirtyIndexes.append(x);
            }
        }
        if (dirtyIndexes.count() == 0) {
            appendProduct(); //установить id не удалось, добавляем пустой продукт
        } else if (dirtyIndexes.count() == 1) {
            // если артикул единственный - pid наш
            int rowIndx = dirtyIndexes.at(0);
            QVector<QString> row = dirtyRes.at(rowIndx);
            appendProduct(row);
        } else {
            QString currDescription = descriptions.at(i);
            currDescription.replace(QRegExp("[^0-9A-я]"), "");
            // если артикулов несколько - ищем нужный, сопостовляя
            // наименование продукта
            bool unknownArt = true;
            foreach (int indx, dirtyIndexes) {
                QVector<QString> row = dirtyRes.at(indx);
                QString tmpDescription = row.at(2);
                tmpDescription.replace(QRegExp("[^0-9A-я]"), "");
                if (currDescription == tmpDescription) {
                    appendProduct(row);
                    unknownArt = false;
                    break;
                }
            }
            if (unknownArt) {
                appendProduct(); // артикул все равно не удалось найти
            }
        }
    }
}

void Store::appendProduct()
{
    products->append(new NewProduct());
}

void Store::appendProduct(const QSqlRecord &rec)
{
    NewProduct *p;
    p->setArticle(rec.value("art").toString());
    p->setDescription(rec.value("description").toString());
    p->setMain_mult(rec.value("main_mult").toInt());
    p->setMain_unit(rec.value("main_unit").toString());
    p->setMid(rec.value("mid").toInt());
    QVariant pid = rec.value("pid");
    if (pid.isValid()) p->setPid(pid.toInt());
    p->setSec_mult(rec.value("sec_mult").toInt());
    p->setSec_unit(rec.value("sec_unit").toString());
    products->append(p);
}

void Store::appendProduct(const QVector<QString> &row)
{
    NewProduct *p;
    p->setPid(row.at(0).toInt());
    p->setArticle(row.at(1));
    p->setDescription(row.at(2));
    p->setMid(row.at(3).toInt());
    p->setMain_unit(row.at(4));
    p->setMain_mult(row.at(5).toInt());
    p->setSec_unit(row.at(6));
    p->setSec_mult(row.at(7).toInt());
    products->append(p);
}

QList<NewProduct *> *Store::getProducts() const
{
    return products;
}
