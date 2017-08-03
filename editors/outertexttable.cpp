#include "outertexttable.h"
#include <qdebug.h>
#include <qsqlquery.h>
#include <QVectorIterator>
#include <qmessagebox.h>
#include <QMapIterator>
#include "editors/keywordseditor.h"
#include "editors/prodeditor.h"

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
    QVector<QVector<QString>> tableCopy = table;
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
    //если индексов не обнаружено - собираем номера элементов в контейнер
    if (!relationCols.isEmpty()) {
        QMap<int, QVector<int>> preInsert;
        foreach (int col, relationCols) {
            QVector<int> tmpRows;
            for (int row = 0; row < table.size(); row++) {
                QVector<QString> &vec = table[row];
                QString indexValue = getIndexValue(vec[col].simplified(), col);
                if (indexValue.isEmpty()) {
                    tmpRows.append(row);
                } else {
                    vec[col] = indexValue;
                }
            }
            if (!tmpRows.isEmpty()) {
                preInsert.insert(col, tmpRows);
            }
        }

        //если найдены данные, отсутсвующие в индексной таблице - выводим пользователю сообщение
        //о том что надо либо их удалить, либо внести в индексные таблицы
        if (!preInsert.isEmpty()) {
            QList<int> rowsToDelete;
            QMapIterator<int, QVector<int>> it(preInsert);
            while(it.hasNext()){
                it.next();
                QVector<int> rows = it.value();
                QString missingVals;
                QStringList missingValsList;
                for (int row = 0; row < rows.count(); ++row) {
                    missingValsList.append(table.at(rows.at(row)).at(it.key()));
                    missingVals.append(table.at(rows.at(row)).at(it.key()) + ", ");
                }
                missingVals = missingVals.left(missingVals.count() - 2);
                QString relTable = model->relation(it.key()).tableName();
                QMessageBox *message = new QMessageBox(QMessageBox::Warning,
                                                       "Введены недопустимые значения",
                                                       "В таблице " + relTable + " отсутствуют значения: " + missingVals + ", вставка данной строки невозможна. Внести их в исходную таблицу?",
                                                       QMessageBox::Yes | QMessageBox::No);
                if (message->exec() == QMessageBox::Yes) {
                    //вносим изменения, вызывая конструктор редактора индексной таблицы
                    //не забываем сделать submit чтобы данные гарантированно зафиксировались
                    if (relTable == "keywords") {
                        KeywordsEditor *ke = new KeywordsEditor(relTable, missingValsList);
                        ke->exec();
                        delete ke;
                    } else if (relTable == "products") {
                        ProdEditor *pe = new ProdEditor(relTable, missingValsList);
                        pe->exec();
                        delete pe;
                    } else {
                        QMessageBox::critical(NULL, "Ошибка вставки отсутствующих данных",
                                              "Редактор значений таблицы " + relTable + " не содержит конструктора для массовой вставки отсутствующих значений.");
                    }
                    //QSqlQuery insQuery("INSERT INTO " + tableName + "(`" + displayColumn + "`) VALUES('" + displayVal + "')");

                    table = tableCopy;
                    replaceDisplayDataToIndex();
                } else {
                    foreach (int row, rows) {
                        if (rowsToDelete.indexOf(row) < 0) {
                            rowsToDelete.append(row);
                        }
                    }
                }
            }

            //удаляем из исходной таблицы table строки, которые пользователь решил удалить

            std::sort(rowsToDelete.begin(), rowsToDelete.end());
            qDebug() << rowsToDelete;
            for (int row = rowsToDelete.count()-1; row >= 0; --row) {
                 qDebug() << "*it" << rowsToDelete.at(row);
                 table.remove(rowsToDelete.at(row));
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
        return QString();
    }
    return query.value(indexColumn).toString();
}
