#include "import/nomenclature.h"
#include "ui_importdata.h"
#include <qdebug.h>
#include <qsqltablemodel.h>

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

    int col1 = ui->leFirstCol->text().toInt()-1;
    int col2 = ui->leSecCol->text().toInt()-1;
    int col3 = ui->leThirdCol->text().toInt()-1;

    //читаем csv
    QString queryPattern = "INSERT INTO products(art, description, unit, mid) VALUES (";
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
           if (item[col1] == "") continue;
                values.append("'" + item[col1] + "', ");
                values.append("'" + item[col2] + "', ");
                values.append("'" + item[col3] + "', ");
                values.append("'" + QString::number(mid) + "')");
                statement.exec(queryPattern + values);
                values.clear();
                counter++;
                if(counter%10) ui->progressBar->setValue(counter);
            }
            ui->progressBar->setValue(rowCount);
            stream.flush();
        }

    statement.exec("COMMIT");

    csvFile.close();
    csvFile.remove();

    ui->progressBar->setVisible(false);
}
