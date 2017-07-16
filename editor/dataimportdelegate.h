#ifndef DATAIMPORTDELEGATE_H
#define DATAIMPORTDELEGATE_H

#include <qvector.h>
#include <qtableview.h>
#include <qsqlrelationaltablemodel.h>



class DataImportDelegate
{
public:
    DataImportDelegate(QTableView &tableView, QSqlRelationalTableModel &model);
    void insertDataFromClipboard();
private:
    QTableView *tableView;
    QSqlRelationalTableModel *model;
    QVector<QVector<QString>> table;
    int currentRow;
private:
    void insertRowsToModel(int rowsToInsert);
    void insertModelData();
    void replaceDisplayDataToIndex();
    QString getIndexValue(int row, int col, QString tableName, QString indexColumn, QString displayColumn, QString value);
};

#endif // DATAIMPORTDELEGATE_H
