#include "import/nomenclature.h"
#include "ui_importdata.h"
#include <qdebug.h>
#include <qsqltablemodel.h>

Nomenclature::Nomenclature()
{
    setWindowTitle("Импорт номенклатуры");
    ui->lbFirstCol->setText("Столбец артикул");
    ui->lbSecCol->setText("Столбец номенклатура");
    ui->lbThirdCol->setText("Столбец ед. изм.");
}

void Nomenclature::onProgressChanged(int value)
{
    ui->progressBar->setValue(value);
}

void Nomenclature::onProgressFinished()
{
    ui->progressBar->setVisible(false);
}

void Nomenclature::dataInsert(int mid, QString csvFilePath, int rowCount)
{
    int startRow = ui->leStartRow->text().toInt()-1;
    int articleCol = ui->leFirstCol->text().toInt()-1;
    int nomenclatureCol = ui->leSecCol->text().toInt()-1;
    int unitCol = ui->leThirdCol->text().toInt()-1;

    ni = new NomenclatureImport(csvFilePath, mid, rowCount,
                                startRow, articleCol,
                                nomenclatureCol, unitCol);
    connect(ni, SIGNAL(progressChanged(int)),
            this, SLOT(onProgressChanged(int)));
    connect(ni, SIGNAL(finished()),
            this, SLOT(onProgressFinished()));
    ni->start();
}


