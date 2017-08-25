#include "import/priceimport.h"
#include "ui_importdata.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qdebug.h>

PriceImport::PriceImport()
{
    setWindowTitle("Импорт базовых цен");
    ui->lbFirstCol->setText("Столбец артикул");
    ui->lbSecCol->setText("Столбец база");
    ui->lbThirdCol->setHidden(true);
    ui->leThirdCol->setHidden(true);
}

void PriceImport::dataInsert(int mid, QString csvFilePath, int rowCount)
{
    Q_UNUSED(rowCount);
    Q_UNUSED(mid);
    //заливка цен
    /*
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
        for (int i(0); i < ui->leStartRow->text().toInt()-1; i++) stream.readLine();
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
    */
}
