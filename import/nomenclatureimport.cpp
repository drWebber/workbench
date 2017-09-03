#include "nomenclatureimport.h"
#include "excel/xlsreader.h"
#include <qfile.h>
#include <qsqlquery.h>
#include <qtextstream.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
#include <qdebug.h>

NomenclatureImport::NomenclatureImport(ImportInfo &import, QObject *parent) :
    QThread(parent)
{
    this->import = import;
}

void NomenclatureImport::run()
{
    XlsReader xr(new QFile(import.getFilePath()));
    xr.openActiveWorkBook();
    QFile *csvFile = xr.saveAsCsv();
    xr.close();
}
