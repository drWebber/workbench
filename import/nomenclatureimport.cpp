#include "nomenclatureimport.h"

#include <qsqlquery.h>
#include <qtextstream.h>
#include <qsqlerror.h>
#include <qdebug.h>
#include "csvreader.h"
#include "dataparcer.h"
#include "datawriter.h"

NomenclatureImport::NomenclatureImport(ImportInfo &import, QObject *parent) :
    QThread(parent)
{
    this->import = import;
}

NomenclatureImport::~NomenclatureImport()
{
    delete csvFile;
}

void NomenclatureImport::run()
{
    emit progressChanged("Чтение xls-файла...");
    XlsReader xr(new QFile(import.getFilePath()));
    xr.openActiveWorkBook();
    csvFile = xr.saveAsCsv();
    xr.close();

    emit progressChanged("Парсинг номенклатуы...");
    CsvReader cr(csvFile, import.getStartRow());
    QList<int> productInfo = QList<int>() << import.getArticleCol()
                                          << import.getDescCol()
                                          << import.getUnitsCol();
    DataParcer prodParcer(productInfo);
    DataWriter prodWriter;
    if (!prodWriter.open(csvFile->fileName() + ".txt")) {
        emit importError("Ошибка открытия файла" + csvFile->fileName() + ".txt");
        return;
    }

    QString mid = import.getMid();
    if (cr.openCsv()) {
        while (!cr.atEnd()) {
            QString line = prodParcer.parceLine(cr.readLine());
            if (!line.isEmpty()) {
                prodWriter.append(line + '\t' + mid);
            }
        }
    } else {
        emit importError("Не удалось прочитать csv...");
        return;
    }
    QThread::sleep(1);

    emit progressChanged("Импорт номенклатуры в бд...");
    QSqlQuery query;
    if (!query.exec("LOAD DATA INFILE '" + prodWriter.getFilePath()
                   + "' INTO TABLE `products`(`art`, `description`, `main_unit`, `mid`)")) {
        emit importError(query.lastError().text());
    }
    QThread::sleep(1);
    emit progressChanged("Импорт завершен");
}
