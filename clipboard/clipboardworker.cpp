#include "clipboard/clipboardworker.h"
#include <qapplication.h>
#include <qdebug.h>

ClipboardWorker::ClipboardWorker()
{
    QClipboard *localClipboard = QApplication::clipboard();
    clipboardText = localClipboard->text();
}

QVector<QVector<QString> > ClipboardWorker::lastTable() const
{
    return table;
}

QVector<QVector<QString> > ClipboardWorker::getTable()
{
    /*
     * В буфере должна сордераться "эксель-подобная" таблица, в которой ячейки отделены табом \t,
     * а строки - символом перехода на новую строку \n. В данном методе по регулярным выражениям отбора
     * таких "строк" и "колонок" формируем итоговый двумерный вектор строковых типов.
     */

    //ходим по строкам
    QRegularExpression row_rx("(.+?)[^\\\\]\n");
    QRegularExpressionMatchIterator row_it = row_rx.globalMatch(clipboardText);
    while(row_it.hasNext()){
        QVector<QString> temp;
        QRegularExpressionMatch row_match = row_it.next();        
        //ходим по столбцам
        QRegularExpression col_rx("(.+?)(?:\t|\n)");
        QRegularExpressionMatchIterator col_it = col_rx.globalMatch(row_match.captured());
        while(col_it.hasNext()){
            QRegularExpressionMatch col_match = col_it.next();
            temp.append(col_match.captured(1));
        }
        table.append(temp);
    }
    return table;
}

bool ClipboardWorker::isTable()
{
    return (clipboardText.indexOf("\t") != -1 || clipboardText.indexOf("\n") != -1) ? true : false;
}
