#include "editor/dataimportdelegate.h"
#include <qclipboard.h>
#include <qregularexpression.h>
#include <qsqlquery.h>
#include <qapplication.h>
#include <qdebug.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
#include "clipboard/clipboardworker.h"

DataImportDelegate::DataImportDelegate(QTableView &tableView, QSqlRelationalTableModel &model)
{
    this->tableView = &tableView;
    this->model = &model;
    currentRow = tableView.currentIndex().row();
}

void DataImportDelegate::insertDataFromClipboard()
{
    ClipboardWorker cw;
    qDebug() << "buf contains table" << cw.isTable();
    table = cw.getTable();

    insertRowsToModel(table.count()-1); // -1 т.к. вставка будет производиться начиная уже с текущей ячейки модели

    replaceDisplayDataToIndex();

    insertModelData();
}

void DataImportDelegate::insertRowsToModel(int rowsToInsert)
{
    //currentRow + 1, т.к. rowCount считает общее число строк, а currentRow - показывает нумерацию с нуля
    if (rowsToInsert > tableView->model()->rowCount() - currentRow) {
        model->insertRows(tableView->currentIndex().row(), rowsToInsert);
    }
}

void DataImportDelegate::insertModelData()
{
/*  Вставляем "преобразованные" данные в модель (отображаемые значения подготовленных к вставке данных
    заменены индексы по установленным отношениям */

    foreach (QVector<QString> vector, table) {
        int col = tableView->currentIndex().column();
        foreach (QString str, vector) {
            qDebug() << "str" << str;
            tableView->model()->setData(tableView->model()->index(currentRow, col), str, Qt::EditRole);
            //For relational columns, value must be the index, not the display value.
            //The index must also exist in the referenced table, otherwise the function returns false.
            qDebug() << tableView->model()->data(tableView->model()->index(currentRow, col)).toString();
            col++;
        }
        currentRow++;
    }
}

void DataImportDelegate::replaceDisplayDataToIndex()
{
    //если у таблицы установлены отношения, в векторе меняем значения ячеек с отображаемого значения на соотв. индексы
    for (int i = 0; i < model->columnCount(); ++i) {
        QString tableName = model->relation(i).tableName();
        QString indexColumn = model->relation(i).indexColumn();
        QString displayColumn = model->relation(i).displayColumn();

        for (int j = 0; j < table.size(); ++j) {
            if (!tableName.isEmpty()) {
                QString indexValue = getIndexValue(i, j, tableName, indexColumn, displayColumn, table[j].data()[i]).simplified();
                if (!indexValue.isEmpty()) {
                    table[j].data()[i] = indexValue;
                }
            }
        }
    }
}

QString DataImportDelegate::getIndexValue(int row, int col, QString tableName, QString indexColumn, QString displayColumn, QString value)
{
    QSqlQuery query;
    query.prepare("SELECT " + indexColumn + " FROM " + tableName + " WHERE " + displayColumn + " = :value");
    query.bindValue(":value", value);
    query.exec();
    if(!query.next()){
        qDebug() << "************** insert ************";
//        QMessageBox::information(NULL, "123", "123");
        //здесь спросить у пользователя че делать, вносить в таблицу новое значение, или нах забить на эту сроку
        QSqlQuery insQuery("INSERT INTO " + tableName + "(`" + displayColumn + "`) VALUES('" + value + "')");
        //model->setData(tableView->model()->index(row, col), value, Qt::EditRole);

        model->select();
        model->insertRow(currentRow);
        table.clear();
        insertDataFromClipboard();


//        QMessageBox::information(NULL, "123", "before ret");
//        return getIndexValue(row, col, tableName, indexColumn, displayColumn, value);
    }
    return query.value(indexColumn).toString();
}
