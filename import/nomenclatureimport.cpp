#include "nomenclatureimport.h"

#include <qfile.h>
#include <qsqlquery.h>
#include <qtextstream.h>
#include <qsqlerror.h>
#include <qmessagebox.h>

#include <qdebug.h>

NomenclatureImport::NomenclatureImport(QString &csvFilePath, QProgressBar &progressBar,
                                       int &mid, int &rowCount, const int &startRow, const int &articleCol,
                                       const int &nomenclatureCol, const int &unitCol, QObject *parent) :
    QThread(parent)
{
    this->csvFilePath = csvFilePath;
    this->progressBar = &progressBar;
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



void NomenclatureImport::sqlMultiplicyInsert(const QString &article, const QString &mid,
                                             const QString &unit)
{
    QSqlQuery multQuery;
    multQuery.prepare("INSERT INTO multiplicy(pid, main_unit) VALUES((SELECT pid FROM products WHERE art = :art AND mid = :mid), :unit)");
    multQuery.bindValue(":art", article);
    multQuery.bindValue(":mid", mid);
    multQuery.bindValue(":unit", unit);
    if(!multQuery.exec()){
        qDebug() << "muilt insertion error";
        qDebug() << article << mid << unit;
        printSqlError(multQuery);
    }
}

void NomenclatureImport::sqlProductInsert(const QString &article, const QString &description,
                                    const QString &mid, const QString unit)
{
    QSqlQuery insQuery;
    insQuery.prepare("INSERT INTO products(art, description, mid) VALUES(:art, :desc, :mid)");
    insQuery.bindValue(":art", article);
    insQuery.bindValue(":desc", description);
    insQuery.bindValue(":mid", mid);
    if (!insQuery.exec()) {
        qDebug() << "Ошибка внесения номенклатуры";
        qDebug() << article << description << unit;
        printSqlError(insQuery);
    } else {
        sqlMultiplicyInsert(article, mid, unit);
    }
}

void NomenclatureImport::run()
{
    QSqlQuery statement;
    statement.exec("START TRANSACTION");

    int maxCol = max(articleCol, nomenclatureCol, unitCol);

    //читаем csv
    QFile csvFile(csvFilePath);
    if(csvFile.open(QFile::ReadOnly | QFile::Text)) {
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
                sqlProductInsert(article, desc, QString::number(mid), item[unitCol]);
                counter++;
                if(counter%10) progressBar->setValue(counter);
            }
        }
        progressBar->setValue(rowCount);
        stream.flush();
    } else {
       QMessageBox::warning(0, "Ошибка", "Ошибка открытия файла" + csvFilePath + ".");
    }
    statement.exec("COMMIT");
    csvFile.close();
    csvFile.remove();
    progressBar->setVisible(false);
}
