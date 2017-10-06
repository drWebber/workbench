#include "testingwnd.h"
#include "ui_testingwnd.h"

TestingWnd::TestingWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestingWnd)
{
    ui->setupUi(this);

    QStringList tests = QStringList() << "Store::Store(const QList<int> pids)"
                                      << "Store(const QStringList articles, const int mid);"
                                      << "Store(const QStringList articles, const QStringList descriptions);";

    ui->cbTestNum->addItems(tests);
}

TestingWnd::~TestingWnd()
{
    delete ui;
    delete t1;
    delete source;
    delete pModel;
    delete t2;
    delete t3;
}

void TestingWnd::on_pbnTest_clicked()
{
    int testNum = ui->cbTestNum->currentIndex();
    switch (testNum) {
    case 0:
        t1 = new Test1();
        source = t1->getSourceModel();
        pModel = t1->getResultModel();
        ui->tbvSource->setModel(source);
        ui->tbvTest->setModel(pModel);
        break;
    case 1:
        t2 = new Test2();
        break;
    case 2:
        t3 = new Test3();
        break;
    default:
        break;
    }
}
