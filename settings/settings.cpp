#include "settings.h"
#include "ui_settings.h"

#include <qfiledialog.h>
#include <qdebug.h>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->leBupDirPath->setText(settings.value("BackupDir").toString());
    ui->leMysqlDumpPath->setText(settings.value("MySqlDumpPath").toString());
}

Settings::~Settings()
{
    delete ui;
}

QString Settings::browseDir()
{
    return QFileDialog::getExistingDirectory() + "/";
}

QString Settings::browseFile()
{
    return QFileDialog::getOpenFileName();
}

void Settings::on_pbnBrowseMysqlDump_clicked()
{
    QString path = browseFile();
    if (!path.isEmpty()) ui->leMysqlDumpPath->setText(path);
}

void Settings::on_pbhBrowseBupDir_clicked()
{
    QString path = browseDir();
    if (!path.isEmpty()) ui->leBupDirPath->setText(path);
}

void Settings::on_pbnSaveSettings_accepted()
{
    settings.setValue("MySqlDumpPath",
                        QVariant(ui->leMysqlDumpPath->text()));
    settings.setValue("BackupDir",
                        QVariant(ui->leBupDirPath->text()));
    this->close();
}

void Settings::on_pbnSaveSettings_rejected()
{
    this->close();
}
