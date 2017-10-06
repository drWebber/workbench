#ifndef TESTINGWND_H
#define TESTINGWND_H

#include <QDialog>
#include "test/test1.h"
#include "test/test2.h"
#include "test/test3.h"
#include "product-selection/productinfomodel.h"
#include "qsqlquerymodel.h"

namespace Ui {
class TestingWnd;
}

class TestingWnd : public QDialog
{
    Q_OBJECT

public:
    explicit TestingWnd(QWidget *parent = 0);
    ~TestingWnd();

private slots:
    void on_pbnTest_clicked();
private:
    Ui::TestingWnd *ui;
    Test1 *t1;
    QSqlQueryModel *source;
    ProductInfoModel *pModel;
    Test2 *t2;
    Test3 *t3;
};

#endif // TESTINGWND_H
