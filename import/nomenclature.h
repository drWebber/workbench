#ifndef NOMENCLATURE_H
#define NOMENCLATURE_H
#include "importdata.h"
#include "nomenclatureimport.h"

namespace Ui {
    class Nomenclature;
}

class Nomenclature : public ImportData
{
    Q_OBJECT
public:
    explicit Nomenclature();
private slots:
    void onProgressChanged(int value);
    void onProgressFinished();
private:
    NomenclatureImport *ni;
    void dataInsert(int mid, QString csvFilePath, int rowCount);
};

#endif // NOMENCLATURE_H
