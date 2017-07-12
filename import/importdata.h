#ifndef IMPORTDATA_H
#define IMPORTDATA_H

#include <QWidget>
#include <qsettings.h>
#include "sql/sqlquery.h"
#include <qfiledialog.h>

namespace Ui {
class ImportData;
}

class ImportData : public QWidget
{
    Q_OBJECT

public:
    explicit ImportData(QWidget *parent = 0);
    ~ImportData();
private:
    int xlsToCsv(QString xlsFilePath, QString csvFilePath);
    virtual void dataInsert(int mid, QString csvFilePath, int rowCount) = 0;
public slots:
    void slotShowChooseFileDlg();
    void slotSaveCurrSettings();
    void slotLoadSettings();
    void slotImportData();
protected:
    //переменные
    Ui::ImportData *ui;
    QString filePath;
    QSettings *settings;    
    SqlQuery query;
};

#endif // IMPORTDATA_H
