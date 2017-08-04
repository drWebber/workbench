#include "productconstructor.h"
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
#include <qsqlrecord.h>

#include <qdebug.h>

ProductConstructor::ProductConstructor(QList<QLabel *> &labels, QList<QLineEdit *> edits)
{
    this->labels = labels;
    this->edits = edits;
}

bool ProductConstructor::setProductPatterns(const QString &keyword)
{
    clearLabels();

    QSqlQuery query;
    query.prepare("SELECT * FROM patterns WHERE kid = (SELECT kid FROM keywords WHERE name = :name)");
    query.bindValue(":name", keyword);
    query.exec();
    QSqlRecord record = query.record();
    if (!query.next())
    {
        QMessageBox::warning(NULL, "Ошбика", "Шаблон подбора для ключа <b>" +
                             keyword.toUpper() + "</b> не найден!");
        return false;
    }

    int counter = 0;
    foreach (QLabel *label, labels) {
        int indx = record.indexOf("val" + QString::number(++counter));
        label->setText(query.value(indx).toString());
    }

    query.clear();
    return true;
}

void ProductConstructor::clearLabels()
{
    foreach (QLabel *label, labels) {
        label->setText("");
    }
}
