#include "testingwnd.h"
#include "ui_testingwnd.h"
#include "qdebug.h"

TestingWnd::TestingWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestingWnd)
{
    ui->setupUi(this);

    QStringList tests = QStringList() << "Store::Store(const QList<int> pids)"
                                      << "Store(const QStringList articles, const int mid);"
                                      << "Store(const QStringList articles, const QStringList descriptions);"
                                      << "Warehouse";

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
    case 3:
        {
            Warehouse w;
            w.load();
            Warehouse w1 = w.find(4, Warehouse::OTHER);
            qDebug() << "MID:4, location: Внешнее. Ожидаемый smid: 3, возвращаемый:"
                     << w1.getSmid() << "валидность:" << w1.isValid(w1);
            Warehouse w2 = w.find(444, Warehouse::VITEBSK);
            qDebug() << "НЕВЕРНЫЕ ДАННЫЕ - MID:444, location: Витебск."
                        " Ожидаемый smid: -1, возвращаемый:"
                     << w2.getSmid() << "валидность:" << w2.isValid(w2);
            Warehouse w3 = w.find(11, Warehouse::MINSK);
            qDebug() << "MID:11, location: Минск. Ожидаемый smid: 4, возвращаемый:"
                     << w3.getSmid() << "валидность:" << w3.isValid(w3);
        }
        break;
    default:
        break;
    }
}
