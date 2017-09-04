#include "nomenclatureimport.h"

#include <qsqlquery.h>
#include <qtextstream.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
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
    xr->close();
    delete csvFile;
    delete xr;
}

void NomenclatureImport::run()
{
    xr = new XlsReader(new QFile(import.getFilePath()));
    xr->openActiveWorkBook();
    csvFile = xr->saveAsCsv();
    CsvReader cr(csvFile, import.getStartRow());
    QList<int> productInfo = QList<int>() << import.getArticleCol()
                                          << import.getDescCol();
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
    QSqlQuery("LOAD DATA INFILE '" + prodWriter.getFilePath()
              + "' INTO TABLE `products`(`art`, `description`, `mid`)").exec();
}
