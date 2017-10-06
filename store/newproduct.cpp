#include "store/newproduct.h"

NewProduct::NewProduct()
{

}

int NewProduct::getPid() const
{
    return pid;
}

void NewProduct::setPid(int value)
{
    pid = value;
}

int NewProduct::getMid() const
{
    return mid;
}

void NewProduct::setMid(int value)
{
    mid = value;
}

int NewProduct::getMain_mult() const
{
    return main_mult;
}

void NewProduct::setMain_mult(int value)
{
    main_mult = value;
}

int NewProduct::getSec_mult() const
{
    return sec_mult;
}

void NewProduct::setSec_mult(int value)
{
    sec_mult = value;
}

QString NewProduct::getArticle() const
{
    return article;
}

void NewProduct::setArticle(const QString &value)
{
    article = value;
}

QString NewProduct::getDescription() const
{
    return description;
}

void NewProduct::setDescription(const QString &value)
{
    description = value;
}

QString NewProduct::getMain_unit() const
{
    return main_unit;
}

void NewProduct::setMain_unit(const QString &value)
{
    main_unit = value;
}

QString NewProduct::getSec_unit() const
{
    return sec_unit;
}

void NewProduct::setSec_unit(const QString &value)
{
    sec_unit = value;
}

bool NewProduct::isValid()
{
    return pid != -1 ? true : false;
}
