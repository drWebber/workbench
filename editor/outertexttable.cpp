#include "outertexttable.h"
#include <qdebug.h>
#include <qsqlquery.h>
#include <QVectorIterator>
#include <qmessagebox.h>
#include <QMapIterator>

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
    //если индексов не обнаружено - собираем номера элементов в контейнер
    if (!relationCols.isEmpty()) {
        foreach (int col, relationCols) {
            QVector<int> tmpRows;
            for (int row = 0; row < table.size(); row++) {
                QVector<QString> &vec = table[row];
                QString indexValue = getIndexValue(vec[col].simplified(), col);
                if (indexValue.isEmpty()) {
                    делаем выбор прямо здесь!!!!!!!!!!!!!!!!!!!!!
                            если выбор за - перезапускаем getIndexValue() и вносим в вектор, либо удаляем нах!!!
                            переделать цикл на хотьбу сначала по строкам, потом по колонкам!!!!!
                    tmpRows.append(row);
                } else {
                    vec[col] = indexValue;
                }
            }
            if (!tmpRows.isEmpty()) {
                preInsert.insert(col, tmpRows);
            }
        }
    }

    //если найдены данные, отсутсвующие в индексной таблице - выводим пользователю сообщение
    //о том что надо либо их удалить, либо внести в индексные таблицы
    if (!preInsert.isEmpty()) {
        QMapIterator<int, QVector<int>> it(preInsert);
        while(it.hasNext()){
            it.next();
            QVector<int> rows = it.value();
            QString emptyKeyValues;
            for (int row = 0; row < rows.count(); ++row) {
                emptyKeyValues.append(table.at(rows.at(row)).at(it.key()) + ", ");
            }
            emptyKeyValues = emptyKeyValues.left(emptyKeyValues.count() - 2);
            QMessageBox *message = new QMessageBox(QMessageBox::Warning,
                                                   "Введены недопустимые занчения",
                                                   "В таблице " + model->relation(it.key()).tableName() + " отсутствуют значения: " + emptyKeyValues + ", вставка данной строки невозможна. Внести их в исходную таблицу?",
                                                   QMessageBox::Yes | QMessageBox::No);
            if (message->exec() == QMessageBox::Yes) {
                //вносим изменения, вызывая конструктор редактора индексно таблицы
                //не забываем сделать submit чтобы данные гарантированно зафиксировались
            } else {
                foreach (int row, rows) {
                    qDebug() << "remove row:" << row;
                    qDebug() << table.count();
                    table.remove(row);
                    qDebug() << "error is not here";
                }
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
//        QSqlQuery insQuery("INSERT INTO " + tableName + "(`" + displayColumn + "`) VALUES('" + displayVal + "')");
        return QString();
    }
    return query.value(indexColumn).toString();
}
