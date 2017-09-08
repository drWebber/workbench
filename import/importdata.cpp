#include "ui_importdata.h"
#include "import/importdata.h"
#include <qdebug.h>
#include <QShortcut>

ImportData::ImportData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportData)
{
    ui->setupUi(this);
    ui->pbImport->setEnabled(false);

    QStringList list = query.getSingleValsList("SELECT name FROM manufacturers");
    ui->cbManufacturer->addItems(list);
    ui->cbManufacturer->setCurrentIndex(-1);

    QIcon icon;
    icon.addPixmap(QPixmap(":/images/terminal.png"));
    this->setWindowIcon(icon);

    icon.addPixmap(QPixmap(":/images/savesettings.png"));
    ui->tbSaveCurrSettings->setIcon(icon);

    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close()));
    settings = new QSettings("drwebber's soft", "workbench");

    show();
}

ImportData::~ImportData()
{
    delete ui;
}


void ImportData::slotShowChooseFileDlg()
{
    QDir::setCurrent("d:\\Каталоги\\Номенклатура 11.08.17\\");
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

    QString name =  ui->cbManufacturer->currentText();

    this->dataInsert();
}
