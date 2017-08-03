#ifndef PRICEIMPORT_H
#define PRICEIMPORT_H
#include "importdata.h"



class PriceImport : public ImportData
{
public:
    PriceImport();
private:
    void dataInsert(int mid, QString csvFilePath, int rowCount);
public slots:
    void slotShowChooseFileDlg();
};

#endif // PRICEIMPORT_H
