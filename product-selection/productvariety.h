#ifndef PRODUCTVARIETY_H
#define PRODUCTVARIETY_H

#include <qstring.h>
#include <qsqlquery.h>
#include <qlineedit.h>

class ProductVariety
{
public:
    ProductVariety(QList<QLineEdit *> lineEdits);
    QStringList getFilter(const QString &key);
    QVector<QStringList> getStoreRemainings(const QList<int> &pids, const QList<int> &mids);
private:
    QStringList getItemRemainings(const int &pid, const int &mid);
    QSqlQuery *query;
    QList<QLineEdit *> lineEdits;
};

#endif // PRODUCTVARIETY_H
