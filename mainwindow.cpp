#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql/sqlquery.h"
#include <qtableview.h>
#include <QLabel>
#include <qevent.h>
#include <qstandarditemmodel.h>
#include <QThread>

enum colNames {
    col_pid, col_art, col_desc, col_mid
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    SqlConn sc = SqlConn();
    sc.connect();

    QSqlQuery query;
    query.exec("SET NAMES 'cp1251'");

    sq = new SqlQuery();

    ui->leKey->installEventFilter(this);

    labels << ui->lbPatt1 << ui->lbPatt2 << ui->lbPatt3 << ui->lbPatt4
           << ui->lbPatt5 << ui->lbPatt6 << ui->lbPatt7;

    lineEdits << ui->leVal1 << ui->leVal2 << ui->leVal3 << ui->leVal4
              << ui->leVal5 << ui->leVal6 << ui->leVal7;



    pc = new ProductConstructor(labels, lineEdits);
    foreach (QLineEdit *edit, lineEdits) {
        edit->installEventFilter(pc);
    }

    pv = new ProductVariety(lineEdits);

    invoiceModel = new QStandardItemModel(this);
    ui->tbvInvoice->setModel(invoiceModel);

    productModel = new ProductInfoModel(this);
    ui->tableView->setModel(productModel);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    prod = new ProdEditor("products");
    prod->setParent(this, Qt::Window);
    prod->show();
}

void MainWindow::slotMManEditTriggered()
{
    manufacturersEditor = new ManufacturersEditor("manufacturers");
    manufacturersEditor->setParent(this, Qt::Window);
    manufacturersEditor->show();
}

void MainWindow::slotMNomEditTriggered()
{
    nomenclature = new Nomenclature();
//    nomenclature->setParent(this, Qt::Window);
    nomenclature->show();
}

void MainWindow::slotMPriceEditTriggered()
{
//    priceImport = new PriceImport();
//    priceImport->setParent(this, Qt::Window);
//    priceImport->show();
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
    qDebug() << pv->getFilter(ui->leKey->text());
    productModel->selectProducts(pv->getFilter(ui->leKey->text()));
//    sqlmodel->setFilter(pv->getFilter(key, sender));
//    sqlmodel->select();

//    QList<int> mids, pids;
//    for (int i = 0; i < sqlmodel->rowCount(); ++i) {
//        pids.append(sqlmodel->data(sqlmodel->index(i, col_pid)).toInt());
//        mids.append(sqlmodel->data(sqlmodel->index(i, col_mid)).toInt());
//    }

//    pi->setRemainingsData(pv->getStoreRemainings(pids, mids));

}

void MainWindow::on_mMultEdit_triggered()
{
    mult = new MultiplicyEditor("multiplicy");
    mult->setParent(this, Qt::Window);
    mult->exec();
}

void MainWindow::on_mClearAll_triggered()
{
    QStringList tables;
    tables << "keywords" << "manufacturers" << "multiplicy" << "params"
           << "patterns" << "products" << "store" << "store_date" << "store_manufacturer";
    foreach (QString table, tables) {
        QSqlQuery().exec("TRUNCATE TABLE " + table);
    }
}

void MainWindow::on_mClearStoreMan_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `store_manufacturer`");
}

void MainWindow::on_mClearStore_date_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `store_date`");
}

void MainWindow::on_mClearStore_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `store`");
}

void MainWindow::on_mClearPatterns_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `patterns`");
}

void MainWindow::on_mClearParams_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `params`");
}

void MainWindow::on_mClearMultiplicy_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `multiplicy`");
}

void MainWindow::on_mClearManufacturers_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `manufacturers`");
}

void MainWindow::on_mClearkeywords_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `keywords`");
}

void MainWindow::on_mClearProducts_triggered()
{
    QSqlQuery().exec("TRUNCATE TABLE `products`");
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QList<QStandardItem *> items;
    for (int i = 0; i < productModel->columnCount(); ++i) {
        QModelIndex tmp = productModel->index(ui->tableView->currentIndex().row(), i);
        items.append(new QStandardItem(productModel->data(tmp).toString()));
    }
    invoiceModel->appendRow(items);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    //не забываем про installeventfilter для желаемого объекта

    // Для ui->leKey устанавливаем собственный обработчик нажатия tab
    if (watched == ui->leKey) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Tab) {
                    QString key = ui->leKey->text();
                    if (!pc->setProductPatterns(key)) {
                        pc->clearLabels();
                        ui->leKey->setFocus();
                        ui->leKey->setSelection(0, key.length());
                        return true;
                    }
            }
        }
    }
    return false;
}
