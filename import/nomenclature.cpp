#include "import/nomenclature.h"
#include "ui_importdata.h"
#include <qdebug.h>
#include <qsqltablemodel.h>

#include <qsqlerror.h>

Nomenclature::Nomenclature()
{
    setWindowTitle("Импорт номенклатуры");
    ui->lbFirstCol->setText("Столбец артикул");
    ui->lbSecCol->setText("Столбец номенклатура");
    ui->lbThirdCol->setText("Столбец ед. изм.");
}

void Nomenclature::dataInsert(int mid, QString csvFilePath, int rowCount)
{
    QSqlQuery statement;
    statement.exec("START TRANSACTION");

    int articleCol = ui->leFirstCol->text().toInt()-1;
    int nomenclatureCol = ui->leSecCol->text().toInt()-1;
    int unitCol = ui->leThirdCol->text().toInt()-1;

    //читаем csv
    QString productQuery = "INSERT INTO products(art, description, mid) VALUES (";
    QFile csvFile(csvFilePath);
    if(csvFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&csvFile);
        QString values;
        for (int i(0); i < ui->leStartRow->text().toInt()-1; i++) stream.readLine(); //пропускаем нужное число строк
                                                                                     //начало задано в бд остатков
        int counter(0);
        while(!stream.atEnd()){
            QString line = stream.readLine();
            QStringList item = line.split(";");
            if (item.count() > 2) {
                QString article = item[articleCol];
                QString description = item[nomenclatureCol];
                QString unit = item[unitCol];
                if (article == "") continue;
                values.append("'" + article + "', ");
                values.append("'" + description + "', ");
                //                values.append("'" + item[unitCol] + "', ");
                values.append("'" + QString::number(mid) + "')");
                if (!statement.exec(productQuery + values)) {
                    qDebug() << "Ошибка внесения номенклатуры";
                    printSqlError(statement);
                } else {
                    sqlMultiplicyInsert(article, mid, unit);
                }
                values.clear();
                counter++;
                if(counter%10) ui->progressBar->setValue(counter);
            }

        }
        ui->progressBar->setValue(rowCount);
        stream.flush();
    }

    statement.exec("COMMIT");

    csvFile.close();
    csvFile.remove();

    ui->progressBar->setVisible(false);
}

void Nomenclature::printSqlError(QSqlQuery &query)
{
    qDebug() << query.lastError();
    qDebug() << query.last();
}

void Nomenclature::sqlMultiplicyInsert(const QString &article, const int &mid, const QString &unit)
{
    QSqlQuery multQuery;
    multQuery.prepare("INSERT INTO multiplicy(pid, main_unit) VALUES((SELECT pid FROM products WHERE art = :art AND mid = :mid), :unit)");
    multQuery.bindValue(":art", article);
    multQuery.bindValue(":mid", mid);
    multQuery.bindValue(":unit", unit);

    if(!multQuery.exec()){
        qDebug() << "muilt insertion error";
        printSqlError(multQuery);
    }

}
