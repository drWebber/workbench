#include "stockbalance.h"
#include "ui_stockbalance.h"

StockBalance::StockBalance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockBalance)
{
    ui->setupUi(this);
}

StockBalance::~StockBalance()
{
    delete ui;
}
