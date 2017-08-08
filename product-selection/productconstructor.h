#ifndef PRODUCTCONSTRUCTOR_H
#define PRODUCTCONSTRUCTOR_H
#include <qlabel.h>
#include <qlineedit.h>

class ProductConstructor
{
public:
    ProductConstructor(QList<QLabel *> &labels, QList<QLineEdit *> edits);
    bool setProductPatterns(const QString &keyword);
    void clearLabels();
    QStringList getCompletions(int &sender);
private:
    QList<QLabel *> labels;
    QList<QLineEdit *> edits;
    QString keyword;
};

#endif // PRODUCTCONSTRUCTOR_H
