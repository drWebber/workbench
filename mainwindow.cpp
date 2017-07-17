#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql/sqlquery.h"
#include <qtableview.h>
#include <QLabel>

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
    keywordsWin = new KeywordsEditor("keywords");
    keywordsWin->setParent(this, Qt::Window);
    keywordsWin->setEditColumn(1);
    keywordsWin->setWindowTitle("Редактор ключевых слов");
    keywordsWin->show();
}

void MainWindow::slotMPattEditTriggered()
{
    pattWin = new SqlTableWin("patterns");
    pattWin->setRelation(0, QSqlRelation("keywords", "kid", "name"));
    pattWin->setWindowTitle("Редактор шаблонов");
    pattWin->setDelegate(0, new SqlInsDelegate("keywords", "kid", "name"));
    pattWin->show();
}

void MainWindow::slotMParamEditTriggered()
{
    paramWin = new SqlTableWin("params");
    paramWin->setMinimumWidth(1042);
    paramWin->setRelation(0, QSqlRelation("keywords", "kid", "name"));
    SqlInsDelegate *delegate = new SqlInsDelegate("keywords", "kid", "name");
    paramWin->setDelegate(0, delegate);
    paramWin->setRelation(1, QSqlRelation("products", "pid", "art"));
    paramWin->setDelegate(1, new SqlInsDelegate("products", "pid", "art"));
    paramWin->setWindowTitle("Редактор параметров");
    paramWin->connectFirstColEnteredSignal();
    paramWin->show();
}

void MainWindow::slotMProdEditTriggered()
{
    prodWin = new SqlTableWin("products");
    prodWin->setMinimumWidth(1024);
    prodWin->setWindowTitle("Редактор продуктов");
    prodWin->hideCol(0);
    prodWin->setEditColumn(1);
    prodWin->show();
}

void MainWindow::slotMManEditTriggered()
{
    manufacturersWin = new SqlTableWin("manufacturers");
    manufacturersWin->setWindowTitle("Редактор производителей");
    manufacturersWin->hideCol(0);
    manufacturersWin->setEditColumn(1);
    manufacturersWin->show();
}

void MainWindow::slotMNomEditTriggered()
{
    nmcWin = new Nomenclature();
    nmcWin->setWindowTitle("Импорт номенклатуры");
    nmcWin->show();
}

void MainWindow::slotMPriceEditTriggered()
{
    priceImportWnd = new PriceImport();
    priceImportWnd->setWindowTitle("Импорт базовых цен");
    priceImportWnd->show();
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
