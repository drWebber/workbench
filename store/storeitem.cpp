#include "storeitem.h"

StoreItem::StoreItem(NewProduct *p) : NewProduct()
{
    this->setPid(p->getPid());
    this->setArticle(p->getArticle());
    this->setDescription(p->getDescription());
    this->setMain_unit(p->getMain_unit());
    this->setMain_mult(p->getMain_mult());
    this->setSec_unit(p->getSec_unit());
    this->setSec_mult(p->getSec_mult());
    availability.append("unknow store"); // Vitebsk default value
    availability.append("unknow store"); // Minsk default value
    availability.append("unknow store"); // Other default value
}

QString StoreItem::getAvailability(Warehouse::Location location) const
{
    return availability.at(location);
}

void StoreItem::setAvailability(Warehouse::Location location, QString count)
{
    availability[location] = count;
}
