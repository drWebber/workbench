#include "outertexttable.h"
#include <qdebug.h>
#include <qsqlquery.h>
#include <QVectorIterator>

OuterTextTable::OuterTextTable(QVector<QVector<QString> > outerTextTabe, SqlRelationalTableModel *model)
{
    table = outerTextTabe;
    this->model = model;
}

void OuterTextTable::printTable()
{
    foreach (QVector<QString> vector, table) {
        QString output;
        foreach (QString val, vector) {
            output.append(val + " ");
        }
        qDebug() << output;
    }
}

void OuterTextTable::replaceDisplayDataToIndex()
{
    /* Если у таблицы установлены отношения, в векторе меняем значения ячеек с отображаемого
     * на значение соотв. индекса. Ходим построчно по каждой ячейке таблицы, проверяя, установлены
     * ли у нее отношения, если отношения есть - забираем из БД первичный ключ, меняем в таблице
     * отображаемое значение на индексное
     */

    //определяем колонки со связями, сохраняем в лист
    QList<int> relationCols;
    for (int col = 0; col < model->columnCount(); ++col) {
        if (!model->relation(col).tableName().isEmpty()) {
            relationCols.append(col);
        }
    }

    //ходим по листу, заменяя отображаемые значения соотв. ячеек таблицы на индексные
    if (!relationCols.isEmpty()) {
        foreach (int col, relationCols) {
            for (int i = 0; i < table.size(); ++i) {
                QVector<QString> &vec = table[i];
                QString indexValue = getIndexValue(vec[col].simplified(), col);
                vec[col] = indexValue;
            }
        }
    }
}

QVector<QVector<QString> > OuterTextTable::getTable() const
{
    return table;
}

QString OuterTextTable::getIndexValue(QString displayVal, int col)
{
    QString tableName = model->relation(col).tableName();
    QString indexColumn = model->relation(col).indexColumn();
    QString displayColumn = model->relation(col).displayColumn();

    QSqlQuery query;
    query.prepare("SELECT " + indexColumn + " FROM " + tableName + " WHERE " + displayColumn + " = :value");
    query.bindValue(":value", displayVal);
    query.exec();
    if(!query.next()){
        //здесь спросить у пользователя че делать, вносить в таблицу новое значение, или нах забить на эту сроку
        QSqlQuery insQuery("INSERT INTO " + tableName + "(`" + displayColumn + "`) VALUES('" + displayVal + "')");

//        model->select();
//        model->insertRow(currentRow);
//        table.clear();
//        insertDataFromClipboard();
        return getIndexValue(displayVal, col);
    }
    return query.value(indexColumn).toString();
}
