#ifndef STOCKBALANCE_H
#define STOCKBALANCE_H

#include <QDialog>

namespace Ui {
class StockBalance;
}

class StockBalance : public QDialog
{
    Q_OBJECT

public:
    explicit StockBalance(QWidget *parent = 0);
    ~StockBalance();

private:
    Ui::StockBalance *ui;
};

#endif // STOCKBALANCE_H
