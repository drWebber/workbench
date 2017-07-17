#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sql/sqlconn.h"
#include <qsqlrelationaltablemodel.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include "editor/sqltablewin.h"
#include "import/importdata.h"
#include "import/nomenclature.h"
#include "import/priceimport.h"
#include "editor/keywordseditor.h"
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
    void testslot();
    int leKeyEdFinished();
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
    SqlQuery *sq;
    QLabel **lbArr;
    QLineEdit **leArr;
    KeywordsEditor *keywordsWin;
    SqlTableWin *manufacturersWin;
    SqlTableWin *pattWin;
    SqlTableWin *paramWin;
    SqlTableWin *prodWin;
    Nomenclature *nmcWin;
    PriceImport *priceImportWnd;
};

#endif // MAINWINDOW_H
