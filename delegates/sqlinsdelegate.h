#ifndef SQLINSDELEGATE_H
#define SQLINSDELEGATE_H

#include <qitemdelegate.h>
#include <qstringlist.h>
#include <qsqlquery.h>
#include <qsqlerror.h>


class SqlInsDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SqlInsDelegate(QString table,
                   QString column,
                   QString displayColumn,
                   QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
private:
    QSqlQuery *qe;
    QString table, displayColumn, column;
};

#endif // SQLINSDELEGATE_H
