#ifndef NOMENCLATUREIMPORT_H
#define NOMENCLATUREIMPORT_H

#include <qsqlquery.h>
#include <qstring.h>
#include <qthread.h>

class NomenclatureImport : public QThread
{
    Q_OBJECT
public:
    NomenclatureImport(QString &csvFilePath, int &mid, int &rowCount,
                       const int &startRow, const int &articleCol,
                       const int &nomenclatureCol, const int &unitCol,
                       QObject *parent = 0);
private:
    QString csvFilePath;
    int mid, rowCount, startRow, articleCol, nomenclatureCol,  unitCol;
    int max(int i, int j, int k);
    void printSqlError(QSqlQuery &query);
    void sqlProductInsert();
    void readCsv();

    // QThread interface
protected:
    void run() override;
signals:
    int progressChanged(int);
};

#endif // NOMENCLATUREIMPORT_H
