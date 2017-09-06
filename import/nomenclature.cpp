#include "import/nomenclature.h"
#include "ui_importdata.h"
#include "importinfo.h"
#include <qdebug.h>
#include <qsqltablemodel.h>
#include <qmessagebox.h>

Nomenclature::Nomenclature()
{
    setWindowTitle("Импорт номенклатуры");
    ui->lbFirstCol->setText("Столбец артикул");
    ui->lbSecCol->setText("Столбец номенклатура");
    ui->lbThirdCol->setText("Столбец ед. изм.");
}

void Nomenclature::dataInsert()
{
    ImportInfo import;
    import.setFilePath(ui->lbFilePath->text());
    import.setStartRow(ui->leStartRow->text().toInt()-1);
    import.setArticleCol(ui->leFirstCol->text().toInt()-1);
    import.setDescCol(ui->leSecCol->text().toInt()-1);
    import.setUnitsCol(ui->leThirdCol->text().toInt()-1);
    import.setManufacturer(ui->cbManufacturer->currentText());

    ni = new NomenclatureImport(import);
    connect(ni, SIGNAL(importError(QString)), this, SLOT(on_importError(QString)));
    ni->start();
}

void Nomenclature::on_importError(QString msg)
{
    QMessageBox::critical(NULL, "Ошибка импорта в бд", msg);
}


