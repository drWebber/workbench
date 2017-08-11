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
    int maxCol = max(articleCol, nomenclatureCol, unitCol);
    //читаем csv
    QFile csvFile(csvFilePath);
    if(csvFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&csvFile);
        for (int i(0); i < ui->leStartRow->text().toInt()-1; i++) stream.readLine(); //пропускаем нужное число строк
                                                                                     //начало задано в бд остатков
        int counter(0);
        while(!stream.atEnd()){
            QString line = stream.readLine();
            QStringList item = line.split(";");
            if (item.count() > maxCol) {
                QString article = item[articleCol];
                QString desc = item[nomenclatureCol];
                if (article.isEmpty() || desc.isEmpty()) continue;
                sqlProductInsert(article, desc, QString::number(mid), item[unitCol]);
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
}

int Nomenclature::max(int i, int j, int k)
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

void Nomenclature::sqlMultiplicyInsert(const QString &article, const QString &mid, const QString &unit)
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

void Nomenclature::sqlProductInsert(const QString &article, const QString &description,
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
