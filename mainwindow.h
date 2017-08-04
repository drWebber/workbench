#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sql/sqlconn.h"
#include <qsqlrelationaltablemodel.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
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
#include <qstandarditemmodel.h>
#include <qlist.h>

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
private:
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *sqlmodel;
    QStandardItemModel *invoiceModel;
    SqlQuery *sq;
    QList<QLabel *> labels;
    QList<QLineEdit *> lineEdits;
    KeywordsEditor *keywords;
    MultiplicyEditor *mult;
    PattEditor *patt;
    ManufacturersEditor *manufacturersEditor;
    ParamEditor *param;
    ProdEditor *prod;
    Nomenclature *nomenclature;
    PriceImport *priceImport;
    ProductConstructor *pc;
    ProductVariety *pv;
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

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWINDOW_H
