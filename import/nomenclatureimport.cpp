#include "nomenclatureimport.h"

#include <qfile.h>
#include <qsqlquery.h>
#include <qtextstream.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
#include "nomenclaturetxtfile.h"
#include <qdebug.h>

NomenclatureImport::NomenclatureImport(QString &csvFilePath,
                                       int &mid, int &rowCount, const int &startRow, const int &articleCol,
                                       const int &nomenclatureCol, const int &unitCol, QObject *parent) :
    QThread(parent)
{
    this->csvFilePath = csvFilePath;
    this->mid = mid;
    this->rowCount = rowCount;
    this->startRow = startRow;
    this->articleCol = articleCol;
    this->nomenclatureCol = nomenclatureCol;
    this->unitCol = unitCol;
}

int NomenclatureImport::max(int i, int j, int k)
{
    if (i > j) {
        if (i > k) {
            return i;
        } else {
            return k;
        }
    } else if (j > k) {
        return j;
    } else {
        return k;
    }
}

void NomenclatureImport::printSqlError(QSqlQuery &query)
{
    qDebug() << query.lastError();
}

void NomenclatureImport::sqlProductInsert()
{
    QSqlQuery statement;
    statement.exec("START TRANSACTION");

    //импорт номенклатуры из файла
    //импорт кратности упаковки из файла

    statement.exec("COMMIT");
//    QSqlQuery insQuery;
//    insQuery.prepare("INSERT INTO products(art, description, mid) VALUES(:art, :desc, :mid)");
//    insQuery.bindValue(":art", article);
//    insQuery.bindValue(":desc", description);
//    insQuery.bindValue(":mid", mid);
//    if (!insQuery.exec()) {
//        qDebug() << "Ошибка внесения номенклатуры";
//        qDebug() << article << description << unit;
//        printSqlError(insQuery);
//    } else {
//        sqlMultiplicyInsert(article, mid, unit);
//    }
}

void NomenclatureImport::run()
{

    int maxCol = max(articleCol, nomenclatureCol, unitCol);

    //читаем csv
    QFile csvFile(csvFilePath);

    DataWriter textFile(csvFile);

    if (csvFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&csvFile);
        for (int i(0); i < startRow; i++) stream.readLine(); //пропускаем нужное число строк
                                                             //начало задано в бд остатков
        int counter(0);
        while(!stream.atEnd()){
            QString line = stream.readLine();
            if (line.isEmpty()) {
                continue;
            }
            QStringList item = line.split(";");
            if (item.count() > maxCol) {
                QString article = item[articleCol];
                QString desc = item[nomenclatureCol];
                if (article.isEmpty() || desc.isEmpty()) continue;
                textFile.appendNomenclatureRow(article + "\t" + desc + "\t" + QString::number(mid));
                //sqlProductInsert(article, desc, QString::number(mid), item[unitCol]);
                counter++;
                if(counter%10) progressChanged(counter);
            }
        }
        progressChanged(rowCount);
        stream.flush();
    } else {
        QMessageBox::warning(0, "Ошибка",
                             "Ошибка открытия файла" + csvFilePath + ".");
    }

    textFile.appendNomenclatureRow("nomnom");
    textFile.appendMultiplicyRow("mult");
    textFile.closeFiles();

//    if(csvFile.open(QFile::ReadOnly | QFile::Text)) {
//        QTextStream stream(&csvFile);
//        for (int i(0); i < startRow; i++) stream.readLine(); //пропускаем нужное число строк
//                                                                                     //начало задано в бд остатков
//        int counter(0);
//        while(!stream.atEnd()){
//            QString line = stream.readLine();
//            if (line.isEmpty()) {
//                continue;
//            }
//            QStringList item = line.split(";");
//            if (item.count() > maxCol) {
//                QString article = item[articleCol];
//                QString desc = item[nomenclatureCol];
//                if (article.isEmpty() || desc.isEmpty()) continue;
//                //sqlProductInsert(article, desc, QString::number(mid), item[unitCol]);
//                counter++;
//                if(counter%10) progressChanged(counter);
//            }
//        }
//        progressChanged(rowCount);
//        stream.flush();
//    } else {
//       QMessageBox::warning(0, "Ошибка", "Ошибка открытия файла" + csvFilePath + ".");
//    }
    csvFile.close();
    csvFile.remove();
}
