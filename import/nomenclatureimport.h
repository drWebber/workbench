#ifndef NOMENCLATUREIMPORT_H
#define NOMENCLATUREIMPORT_H

#include <qsqlquery.h>
#include <qstring.h>
#include <qthread.h>
#include <qfile.h>
#include "importinfo.h"
#include "excel/xlsreader.h"

class NomenclatureImport : public QThread
{
    Q_OBJECT
public:
    NomenclatureImport(ImportInfo &import, QObject *parent = 0);
    ~NomenclatureImport();
protected:
    void run();
private:
    ImportInfo import;
    QFile *csvFile;
    XlsReader *xr;
};

#endif // NOMENCLATUREIMPORT_H
