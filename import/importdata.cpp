#include "ui_importdata.h"
#include "import/importdata.h"
#include <qdebug.h>
#include <QShortcut>
#include <qaxwidget.h>
#include <qaxobject.h>
#include <qsqlerror.h>
#define xlCSV 6

ImportData::ImportData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportData)
{
    ui->setupUi(this);
    ui->pbImport->setEnabled(false);

    QStringList list = query.getSingleValsList("SELECT name FROM manufacturers");
    ui->cbManufacturer->addItems(list);
    ui->cbManufacturer->setCurrentIndex(-1);

    ui->progressBar->setVisible(false);

    QIcon icon;
    icon.addPixmap(QPixmap(":/images/terminal.png"));
    this->setWindowIcon(icon);

    icon.addPixmap(QPixmap(":/images/savesettings.png"));
    ui->tbSaveCurrSettings->setIcon(icon);

    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close()));
    settings = new QSettings("import.conf", QSettings::IniFormat);

    show();
}

ImportData::~ImportData()
{
    delete ui;
}


void ImportData::slotShowChooseFileDlg()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Выбор файла импорта"), NULL, "*.xls | *.xlsx");
    if (!filePath.isEmpty()) {
        ui->lbFilePath->setText(filePath);
        this->filePath = filePath;
        if(ui->cbManufacturer->currentIndex() != -1) ui->pbImport->setEnabled(true);
    }
}

void ImportData::slotSaveCurrSettings()
{
    settings->beginGroup(this->windowTitle() + ui->cbManufacturer->currentText());
    settings->setValue("start row", ui->leStartRow->text());
    settings->setValue("firstCol", ui->leFirstCol->text());
    settings->setValue("secCol", ui->leSecCol->text());
    settings->setValue("thirdCol", ui->leThirdCol->text());
    settings->endGroup();
}

void ImportData::slotLoadSettings()
{
    settings->beginGroup(this->windowTitle() + ui->cbManufacturer->currentText());
    ui->leStartRow->setText(settings->value("start row", 1).toString());
    ui->leFirstCol->setText(settings->value("firstCol", 1).toString());
    ui->leSecCol->setText(settings->value("secCol", 1).toString());
    ui->leThirdCol->setText(settings->value("thirdCol", 1).toString());
    settings->endGroup();
    if (!filePath.isEmpty() && ui->cbManufacturer->currentIndex() != -1) {
        ui->pbImport->setEnabled(true);
    }
}

void ImportData::slotImportData()
{
    QString xlsFilePath = filePath.replace("/", "\\");
    QString csvFilePath = xlsFilePath.replace(QRegularExpression(".xlsx?"), ".csv").replace("/", "\\");

    int rowCount = this->xlsToCsv(xlsFilePath, csvFilePath);

    ui->progressBar->setVisible(true);
    ui->progressBar->setMaximum(rowCount);

    QString name =  ui->cbManufacturer->currentText();

    int mid = query.getSingleVal("SELECT mid FROM manufacturers WHERE name = '" + name + "'").toInt();

    this->dataInsert(mid, csvFilePath, rowCount);
}

int ImportData::xlsToCsv(QString xlsFilePath, QString csvFilePath)
{
    int rowCount = -1;
    if(!xlsFilePath.isEmpty()){
        QAxWidget excel("Excel.Application");

        QAxObject *workbooks = excel.querySubObject("WorkBooks");
        workbooks->dynamicCall("Open (const QString&)", ui->lbFilePath->text());

        QAxObject *workbook = excel.querySubObject("ActiveWorkBook");

        QAxObject *sheets = workbook->querySubObject("Worksheets");
        QAxObject *sheet = sheets->querySubObject("Item(int)", 1); //1 - "Лист 1"

        QAxObject *range = sheet->querySubObject("UsedRange");

        QAxObject *rows = range->querySubObject("Rows");
        rowCount = rows->dynamicCall("Count()").toInt();

        workbook->dynamicCall("SaveAs (const QString&, const int&)", csvFilePath, xlCSV);

        excel.setProperty("DisplayAlerts", false);
        workbook->dynamicCall("Close (Boolean)", true);

        delete workbook;
        delete workbooks;

        excel.dynamicCall("Quit (void)");
    }
    return rowCount;
}
