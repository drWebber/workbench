#include "sqltablewin.h"
#include "ui_sqltablewin.h"
#include <qsqlquery.h>
#include <qdebug.h>
#include <qmenu.h>
#include <qevent.h>
#include <QPainter>
#include <qlineedit.h>
#include <qsqlrecord.h>

SqlTableWin::SqlTableWin(QString mainSqlTable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlTableWin)
{
    ui->setupUi(this);

    //подключаем меню
    ui->sqlTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->sqlTableView,SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotMenuRequested(QPoint)));

    QIcon icon;
    icon.addPixmap(QPixmap(":/images/terminal.png"));
    this->setWindowIcon(icon);

    QSqlQuery query;
    query.exec("SET NAMES cp1251");
    model = new QSqlRelationalTableModel();
    model->setTable(mainSqlTable);
    model->select();
    ui->sqlTableView->setModel(model);
}

SqlTableWin::SqlTableWin()
{

}

SqlTableWin::~SqlTableWin()
{
    delete ui;
}

void SqlTableWin::setRelation(int col, QSqlRelation rel)
{
    model->setRelation(col, rel);
    model->select();
}

void SqlTableWin::setDelegate(int col, SqlInsDelegate *delegate)
{
    ui->sqlTableView->setItemDelegateForColumn(col, delegate);
}

void SqlTableWin::hideCol(int col)
{
    ui->sqlTableView->hideColumn(col);
}

void SqlTableWin::setEditColumn(int col)
{
    editColumnNum = col;
}


void SqlTableWin::slotDelRow()
{
    int currentRow = ui->sqlTableView->currentIndex().row();
    model->removeRow(currentRow);
    ui->sqlTableView->hideRow(currentRow);
    ui->sqlTableView->selectRow(currentRow-1);
}

void SqlTableWin::slotAddRow()
{
    int rowCount = model->rowCount();
    model->insertRow(rowCount);
    QModelIndex indx = ui->sqlTableView->model()->index(rowCount, editColumnNum);
    ui->sqlTableView->edit(indx);
    ui->sqlTableView->selectRow(rowCount);
}

void SqlTableWin::slotMenuRequested(QPoint pos)
{
    if (ui->sqlTableView->currentIndex().row() != -1) {
        QMenu *menu = new QMenu(this);
        QAction *deleteRec = new QAction("Удалить запись", this);
        connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotDelRow()));
        menu->addAction(deleteRec);
        menu->popup(ui->sqlTableView->viewport()->mapToGlobal(pos));
    }
}

void SqlTableWin::keyPressEvent(QKeyEvent *e){
    const int ESCAPE_KEY = 16777216;
    if (e->key() == ESCAPE_KEY) {
        this->destroy();
    }
}

/*
void SqlTableWin::setCellPlaceholder(int row, int col, QString text)
{
    qDebug() << "setCellPlaceholder";
    QLineEdit *edt = new QLineEdit;
    QModelIndex indx = ui->sqlTableView->model()->index(row, col);
    ui->sqlTableView->setIndexWidget(indx, edt);
    edt->setPlaceholderText(text);
    model->setData(indx, edt->text(), Qt::DisplayRole);
    edt->setText(edt->text());
}*/

void SqlTableWin::connectFirstColEnteredSignal()
{
    connect(ui->sqlTableView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(slotFirstRowEntered(QModelIndex)));
}

void SqlTableWin::slotFirstRowEntered(QModelIndex indx)
{
    int currRow = ui->sqlTableView->currentIndex().row();
    if (indx.column() == 0){
        QSqlQuery *qe = new QSqlQuery();
        QModelIndex indx = model->index(currRow, 0);

        QString query = "SELECT kid FROM keywords WHERE name = '" + model->data(indx).toString() + "'";
        int value = sqe.getSingleVal(query).toInt();

        query = "SELECT * FROM patterns WHERE kid = '" + QString::number(value) + "'";
        qe->exec(query);
        while(qe->next()){
            QString param;
            QSqlRecord rc = qe->record();
            for (int i(1); i < rc.count()-1; i++){
                param = qe->value(i).toString();
                if (param != "") {
                    ui->sqlTableView->model()->setData(model->index(currRow,i+1), param);
                    //this->setCellPlaceholder(currRow, i+1, param);
                }
            }
        }
    }
}
