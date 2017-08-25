#include "multiplechoice.h"
#include "ui_multiplechoice.h"

#include <qdebug.h>

MultipleChoice::MultipleChoice(const QStringList &params, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultipleChoice)
{
    ui->setupUi(this);
    qDebug() << params << "hello";
    bool conv;
    foreach (QString val, params) {
        int digit = val.toInt(&conv);
        if (!conv) {
            qDebug() << val << "конверсия невозможна!";
        } else {
            qDebug() << val.toInt();
        }
    }
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setSingleStep(100);
}

MultipleChoice::~MultipleChoice()
{
    delete ui;
}
