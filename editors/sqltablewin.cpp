#include "sqltablewin.h"
#include "ui_sqltablewin.h"
#include <qsqlquery.h>
#include <qdebug.h>
#include <qmenu.h>
#include <qevent.h>
#include <QPainter>
#include <qlineedit.h>
#include <qsqlrecord.h>
#include <qclipboard.h>
#include <qmessagebox.h>
#include "clipboard/clipboardworker.h"
#include "outertexttable.h"

SqlTableWin::SqlTableWin(QString tableName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlTableWin)
{
    setUp(tableName);
}

SqlTableWin::SqlTableWin(QString tableName, QStringList valsToInsert, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlTableWin)
{
    setUp(tableName);
}

SqlTableWin::SqlTableWin(QString tableName, int column,
                         QVector<QVector<QString> > tableToInsert, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlTableWin)
{
    int lastRow = ui->sqlTableView->model()->rowCount();
    foreach (QVector<QString> rowToInsert, tableToInsert) {
        foreach (QString valToInsert, rowToInsert) {
            model->setData(model->index(lastRow++, column),
                           valToInsert);
        }
    }
    setUp(tableName);
}

SqlTableWin::~SqlTableWin()
{
    delete ui;
}

void SqlTableWin::onMenuRequested(QPoint pos)
{
    menu = new QMenu(this);

    QAction *paste = new QAction("Вставить значения", this);
    menu->addAction(paste);
    connect(paste, SIGNAL(triggered(bool)),
            this, SLOT(onPasteActionTriggered()));
    menu->popup(ui->sqlTableView->viewport()->mapToGlobal(pos));

    if (ui->sqlTableView->currentIndex().row() != -1) {
        QAction *deleteRec = new QAction("Удалить запись", this);
        connect(deleteRec, SIGNAL(triggered()), this, SLOT(slotDelRow()));
        menu->addAction(deleteRec);        
    }
}

void SqlTableWin::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Escape) {
        emit this->close();
    }
}

void SqlTableWin::onFirstRowEntered(QModelIndex indx)
{
    int currRow = ui->sqlTableView->currentIndex().row();
    if (indx.column() == 0){
        QSqlQuery *qe = new QSqlQuery();
        QModelIndex indx = proxy->index(currRow, 0);

        QString query = "SELECT kid FROM keywords WHERE name = '" + proxy->data(indx).toString() + "'";
        int value = sqe.getSingleVal(query).toInt();

        query = "SELECT * FROM patterns WHERE kid = '" + QString::number(value) + "'";
        qe->exec(query);
        while(qe->next()){
            QString param;
            QSqlRecord rc = qe->record();
            for (int i(1); i < rc.count()-1; i++){
                param = qe->value(i).toString();
                if (param != "") {
                    ui->sqlTableView->model()->setData(proxy->index(currRow,i+1), param);
                }
            }
        }
    }
}

void SqlTableWin::onPasteActionTriggered()
{
    ClipboardWorker cw;
    if (cw.isTable()) {
        OuterTextTable outerTable(cw.getTable(), model);
        outerTable.printTable();
        outerTable.replaceDisplayDataToIndex();
        outerTable.printTable();

        QModelIndex beforeReset = ui->sqlTableView->currentIndex();
        model->reselect();
        hideColumns();
        model->setRowsData(beforeReset, outerTable.getTable());
    }
}

void SqlTableWin::on_pbnSave_clicked()
{
    model->submitAll();
}

void SqlTableWin::on_pbnRevert_clicked()
{
    model->revertAll();
}

void SqlTableWin::closeEvent(QCloseEvent *event)
{
    if (model->isDirty()) {
        QMessageBox mBox;
        mBox.setWindowTitle(windowTitle());
        mBox.setText("В таблице есть несохраненные изменения, выйти без сохранения?");
        mBox.setIcon(QMessageBox::Question);

        QAbstractButton *btnSave = mBox.addButton(tr("Сохранить"), QMessageBox::ActionRole);
        QAbstractButton *btnRevert = mBox.addButton(tr("Не сохранять"), QMessageBox::ActionRole);
        QAbstractButton *btnCancel = mBox.addButton(tr("Отмена"), QMessageBox::ActionRole);
        mBox.exec();

        if (mBox.clickedButton() == btnSave) {
            emit ui->pbnSave->clicked(true);
            delete btnSave;
            event->accept();
        } else if (mBox.clickedButton() == btnRevert) {
            emit ui->pbnRevert->clicked(true);
            delete btnRevert;
            event->accept();
        } else {
            delete btnCancel;
            event->ignore();
        }
    }
}

void SqlTableWin::setUp(QString tableName)
{
    ui->setupUi(this);

    ui->bnSetFilter->setIcon(QPixmap(":/images/filter-add-icon.png"));
    ui->bnUnSetFilter->setIcon(QPixmap(":/images/filter-delete-icon.png"));
    ui->bnAdd->setIcon(QPixmap(":/images/Button-Add-icon.png"));
    ui->bnDelete->setIcon(QPixmap(":/images/Button-Delete-icon.png"));

    //подключаем меню
    ui->sqlTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->sqlTableView,SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onMenuRequested(QPoint)));

    model = new SqlRelationalTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    ui->sqlTableView->setModel(proxy);
}

void SqlTableWin::on_bnSetFilter_clicked()
{
    proxy->setFilterKeyColumn(ui->sqlTableView->currentIndex().column());
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterFixedString(ui->leFilter->text());
}

void SqlTableWin::on_bnUnSetFilter_clicked()
{
    proxy->setFilterFixedString("");
}

void SqlTableWin::on_bnAdd_clicked()
{
    int rowCount = proxy->rowCount();
    proxy->insertRow(rowCount);
    ui->sqlTableView->selectRow(rowCount);
}

void SqlTableWin::on_bnDelete_clicked()
{
    int currentRow = ui->sqlTableView->currentIndex().row();
    proxy->removeRow(currentRow);
    ui->sqlTableView->hideRow(currentRow);
    ui->sqlTableView->selectRow(currentRow-1);
}
