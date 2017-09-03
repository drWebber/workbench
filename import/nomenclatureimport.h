#ifndef NOMENCLATUREIMPORT_H
#define NOMENCLATUREIMPORT_H

#include <qsqlquery.h>
#include <qstring.h>
#include <qthread.h>
#include "importinfo.h"

class NomenclatureImport : public QThread
{
    Q_OBJECT
public:
    NomenclatureImport(ImportInfo &import, QObject *parent = 0);
protected:
    void run();
private:
    ImportInfo import;
};

#endif // NOMENCLATUREIMPORT_H
