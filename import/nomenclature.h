#ifndef NOMENCLATURE_H
#define NOMENCLATURE_H
#include "importdata.h"

namespace Ui {
class Nomenclature;
}

class Nomenclature : public ImportData
{
    Q_OBJECT
public:
    explicit Nomenclature();
private:
    void dataInsert(int mid, QString csvFilePath, int rowCount);
public slots:
    //void ImportData::slotShowChooseFileDlg();
};

#endif // NOMENCLATURE_H
