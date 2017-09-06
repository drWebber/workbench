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
    XlsReader xr(new QFile(import.getFilePath()));
    xr.openActiveWorkBook();
    csvFile = xr.saveAsCsv();
//    xr.close();
    CsvReader cr(csvFile, import.getStartRow());
    QList<int> productInfo = QList<int>() << import.getArticleCol()
                                          << import.getDescCol()
                                          << import.getUnitsCol();
    DataParcer prodParcer(productInfo);
    DataWriter prodWriter(csvFile->fileName() + ".txt");
    QString mid = import.getMid();
    if (cr.openCsv()) {
        while (!cr.atEnd()) {
            QString line = prodParcer.parceLine(cr.readLine());
            if (!line.isEmpty()) {
                prodWriter.append(line + '\t' + mid);
            }
        }
    }
    QSqlQuery query;
    if (!query.exec("LOAD DATA INFILE '" + prodWriter.getFilePath()
                   + "' INTO TABLE `products`(`art`, `description`, `mid`, `main_unit`)")) {
        qDebug() << query.lastError().text();
        emit importError(query.lastError().text());
    }
}
