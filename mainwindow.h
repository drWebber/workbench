#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qsqlquery.h>
#include <qcompleter.h>
#include <qstandarditemmodel.h>
#include <qlist.h>
#include <QProcess>
#include "sql/sqlconn.h"
#include "editors/sqltablewin.h"
#include "import/importdata.h"
#include "import/nomenclature.h"
#include "import/priceimport.h"
#include "editors/keywordseditor.h"
#include "editors/manufacturerseditor.h"
#include "editors/parameditor.h"
#include "editors/patteditor.h"
#include "editors/prodeditor.h"
#include "editors/multiplicyeditor.h"
#include "product-selection/productconstructor.h"
#include "product-selection/productvariety.h"
#include "product-selection/productinfomodel.h"
#include "settings/settings.h"
#include "testing/testingwnd.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotMKeyEditTriggered();
    void slotMPattEditTriggered();
    void slotMParamEditTriggered();
    void slotMProdEditTriggered();
    void slotValLeEdtFinished();
    void slotMManEditTriggered();
    void slotMNomEditTriggered();
    void slotMPriceEditTriggered();
    void on_mTestingTriggered();
private:
    Ui::MainWindow *ui;
    QList<QLabel *> labels;
    QList<QLineEdit *> lineEdits;
    QStandardItemModel *invoiceModel;
    SqlQuery *sq;
    KeywordsEditor *keywords;
    MultiplicyEditor *mult;
    PattEditor *patt;
    ManufacturersEditor *manufacturersEditor;
    ParamEditor *param;
    ProdEditor *prod;
    TestingWnd *tw;
    Nomenclature *nomenclature;
    PriceImport *priceImport;
    ProductConstructor *pc;
    ProductVariety *pv;
    ProductInfoModel* productModel;
    Settings *settingsWnd;
    QSettings settings;
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_mMultEdit_triggered();
    void on_mClearAll_triggered();
    void on_mClearStoreMan_triggered();
    void on_mClearStore_date_triggered();
    void on_mClearStore_triggered();
    void on_mClearPatterns_triggered();
    void on_mClearParams_triggered();
    void on_mClearMultiplicy_triggered();
    void on_mClearManufacturers_triggered();
    void on_mClearkeywords_triggered();
    void on_mClearProducts_triggered();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_dbExport();
    void on_dumpFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void on_mSettingsTriggered();
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWINDOW_H
