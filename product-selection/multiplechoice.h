#ifndef MULTIPLECHOICE_H
#define MULTIPLECHOICE_H

#include <QDialog>

namespace Ui {
class MultipleChoice;
}

class MultipleChoice : public QDialog
{
    Q_OBJECT

public:
    explicit MultipleChoice(const QStringList &params, QWidget *parent = 0);
    ~MultipleChoice();

private:
    Ui::MultipleChoice *ui;
};

#endif // MULTIPLECHOICE_H
