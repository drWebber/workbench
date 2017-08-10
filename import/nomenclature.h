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
    void sqlMultiplicyInsert(const QString &article, const QString &mid, const QString &unit);
    void sqlProductInsert(const QString &article, const QString &description,
                          const QString &mid, const QString unit);
    void printSqlError(QSqlQuery &query);
public slots:
    //void ImportData::slotShowChooseFileDlg();
};

#endif // NOMENCLATURE_H
