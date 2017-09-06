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
private:
    NomenclatureImport *ni;
    void dataInsert();
private slots:
    void on_importError(QString msg);
};

#endif // NOMENCLATURE_H
