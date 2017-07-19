#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql/sqlquery.h"
#include <qtableview.h>
#include <QLabel>
#include <qevent.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SqlConn sc = SqlConn();
    sc.connect();

    sq = new SqlQuery();

    lbArr = new QLabel* [7];
    lbArr[0] = ui->lbPatt1;
    lbArr[1] = ui->lbPatt2;
    lbArr[2] = ui->lbPatt3;
    lbArr[3] = ui->lbPatt4;
    lbArr[4] = ui->lbPatt5;
    lbArr[5] = ui->lbPatt6;
    lbArr[6] = ui->lbPatt7;

    leArr = new QLineEdit* [7];
    leArr[0] = ui->leVal1;
    leArr[1] = ui->leVal2;
    leArr[2] = ui->leVal3;
    leArr[3] = ui->leVal4;
    leArr[4] = ui->leVal5;
    leArr[5] = ui->leVal6;
    leArr[6] = ui->leVal7;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testslot()
{

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(0);
    model->setTable("params");


    if (!model->select()) {
        qDebug() << model->lastError();
        qDebug() << QSqlDatabase::database();
    }
    ui->tableView->setModel(model);
}

int MainWindow::leKeyEdFinished()
{
    QSqlQuery query;
    query.exec("SET NAMES 'cp1251'");
    for (int i(0); i < 7; i++) {
        lbArr[i]->text().clear();
    }
    QString keyword = ui->leKey->text();
    query.prepare("SELECT * FROM patterns WHERE kid = (SELECT kid FROM keywords WHERE name = :name)");
    query.bindValue(":name", keyword);
    if (!query.exec())
    {
        qDebug() << "here" << query.lastError().text();
        return 0;
    }
    QSqlRecord rc = query.record();

    query.next();
    for(int i(0); i < 7; i++) {
        int indx = rc.indexOf("val"+QString::number(i+1));
        lbArr[i]->setText(query.value(indx).toString());
    }
    query.clear();
    return 1;
}

void MainWindow::slotMKeyEditTriggered()
{
    keywords = new KeywordsEditor("keywords");
    keywords->setParent(this, Qt::Window);
    keywords->show();
}

void MainWindow::slotMPattEditTriggered()
{
    patt = new PattEditor("patterns");
    patt->setParent(this, Qt::Window);
    patt->show();
}

void MainWindow::slotMParamEditTriggered()
{
    param = new ParamEditor("params");
    param->setParent(this, Qt::Window);
    param->show();
}

void MainWindow::slotMProdEditTriggered()
{
//    prod = new SqlTableWin("products");
//    prod->setMinimumWidth(1024);
//    prod->setWindowTitle("Редактор продуктов");
//    prod->hideCol(0);
}

void MainWindow::slotMManEditTriggered()
{
//    manufacturersWin = new SqlTableWin("manufacturers");
//    manufacturersWin->setWindowTitle("Редактор производителей");
//    manufacturersWin->hideCol(0);
}

void MainWindow::slotMNomEditTriggered()
{
    nomenclature = new Nomenclature();
}

void MainWindow::slotMPriceEditTriggered()
{
    priceImport = new PriceImport();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        QMessageBox mBox(QMessageBox::Warning, windowTitle(), "Вы действительно хотите выйти?",
                                       QMessageBox::Yes | QMessageBox::No, this);
        if (mBox.exec() == QMessageBox::Yes) {
            close();
        }
    }
}

void MainWindow::slotValLeEdtFinished()
{
    QString kid = sq->getSingleVal("SELECT kid FROM keywords WHERE name = '" + ui->leKey->text() + "'").toString();

    QString query = "SELECT pid FROM params WHERE kid = '" + kid + "'";
    int sender = this->sender()->objectName().right(1).toInt();
    for (int i(1); i <= sender; i++){
        QString tmp = leArr[i-1]->text();
        if(tmp != "") query.append(" AND param" + QString::number(i) + " = '" + leArr[i-1]->text() + "'");
    }

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setTable("products");
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    QVector<QString> pids = sq->getSingleVals(query);
    QString where = "pid IN (";
    for (int i(0); i < pids.size(); i++) {
        where.append("'" + pids[i] + "', ");
    }
    where = where.left(where.size()-2);
    where.append(")");
    qDebug() << where;
    model->setFilter(where);
    model->select();
    ui->tableView->setModel(model);
}
