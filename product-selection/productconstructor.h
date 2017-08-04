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
private:
    QList<QLabel *> labels;
    QList<QLineEdit *> edits;
};

#endif // PRODUCTCONSTRUCTOR_H
