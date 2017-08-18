#ifndef NOMENCLATUREIMPORT_H
#define NOMENCLATUREIMPORT_H

#include <qprogressbar.h>
#include <qsqlquery.h>
#include <qstring.h>
#include <qthread.h>

class NomenclatureImport : public QThread
{
    Q_OBJECT
public:
    NomenclatureImport(QString &csvFilePath, QProgressBar &progressBar,
                       int &mid, int &rowCount, const int &startRow, const int &articleCol,
                       const int &nomenclatureCol, const int &unitCol, QObject *parent = 0);
private:
    QProgressBar *progressBar;
    QString csvFilePath;
    int mid, rowCount, startRow, articleCol, nomenclatureCol,  unitCol;
    int max(int i, int j, int k);
    void printSqlError(QSqlQuery &query);
    void sqlMultiplicyInsert(const QString &article, const QString &mid,
                             const QString &unit);
    void sqlProductInsert(const QString &article, const QString &description,
                          const QString &mid, const QString unit);

    // QThread interface
protected:
    void run() override;
};

#endif // NOMENCLATUREIMPORT_H