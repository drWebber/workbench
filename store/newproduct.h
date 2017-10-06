#ifndef NEWPRODUCT_H
#define NEWPRODUCT_H

#include <qstring.h>

class NewProduct
{
public:
    NewProduct();
    int getPid() const;
    void setPid(int value);

    int getMid() const;
    void setMid(int value);

    int getMain_mult() const;
    void setMain_mult(int value);

    int getSec_mult() const;
    void setSec_mult(int value);

    QString getArticle() const;
    void setArticle(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getMain_unit() const;
    void setMain_unit(const QString &value);

    QString getSec_unit() const;
    void setSec_unit(const QString &value);

    bool isValid();
protected:
    int pid = -1;
    int mid = -1;
    int main_mult, sec_mult;
    QString article, description, main_unit, sec_unit;
};

#endif // NEWPRODUCT_H
