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
    virtual void dataInsert() = 0;
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
