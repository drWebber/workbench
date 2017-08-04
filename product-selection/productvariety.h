#ifndef PRODUCTVARIETY_H
#define PRODUCTVARIETY_H

#include <qstring.h>
#include <qsqlquery.h>
#include <qlineedit.h>

class ProductVariety
{
public:
    ProductVariety(QList<QLineEdit *> lineEdits);
    QString getFilter(const QString &key, const int &sender);
private:
    QSqlQuery *query;
    QList<QLineEdit *> lineEdits;
    QStringList pids;
};

#endif // PRODUCTVARIETY_H
