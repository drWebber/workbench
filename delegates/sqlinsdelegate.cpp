#include "delegates/sqlinsdelegate.h"
#include "editors/sqltablewin.h"
#include <qdebug.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qsqlrecord.h>


SqlInsDelegate::SqlInsDelegate(QString table,
                               QString column,
                               QString displayColumn,
                               QObject *parent) :
    QItemDelegate(parent)
{
    this->table = table;
    this->column = column;
    this->displayColumn = displayColumn;
    qe = new QSqlQuery();
}

QWidget *SqlInsDelegate::createEditor(QWidget *parent,
        const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void SqlInsDelegate::setModelData(QWidget *editor,
                     QAbstractItemModel *model,
                     const QModelIndex &index) const
{
    QLineEdit *le = static_cast<QLineEdit*>(editor);
    QString query = "SELECT " + column + " FROM " + table + " WHERE " + displayColumn + " = '" + le->text() + "'";
    qe->exec(query);
    if (!qe->next()){
        QString request = "INSERT INTO " + table + "(" + displayColumn + ") VALUES('" + le->text() + "')";
        qe->exec(request);
        qe->exec("SELECT " + column + " FROM " + table + " WHERE " + displayColumn + " = '" + le->text() + "'");
        qe->next();
    }
    model->setData(index, qe->value(0).toInt(), Qt::EditRole);
}
