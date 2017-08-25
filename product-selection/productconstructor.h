#ifndef PRODUCTCONSTRUCTOR_H
#define PRODUCTCONSTRUCTOR_H
#include <qlabel.h>
#include <qlineedit.h>
#include <qmainwindow.h>
#include <qcompleter.h>
#include "multiplechoice.h"

class ProductConstructor : public QMainWindow
{
public:
    ProductConstructor(QList<QLabel *> &labels, QList<QLineEdit *> edits);
    bool setProductPatterns(const QString &keyword);
    void clearLabels();
    QStringList getCompletions(const QString &sender);
private:
    QList<QLabel *> labels;
    QList<QLineEdit *> edits;
    QString keyword;
    QCompleter* completer;
    MultipleChoice* multChoice;
    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // PRODUCTCONSTRUCTOR_H
