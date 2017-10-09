#ifndef STOREITEM_H
#define STOREITEM_H

#include "store/newproduct.h"
#include "warehouse.h"
#include <qlist.h>


class StoreItem : public NewProduct
{
public:
    StoreItem(NewProduct *p);
    QString getAvailability(Warehouse::Location location) const;
    void setAvailability(Warehouse::Location location, QString count);
private:
    QStringList availability;
};

#endif // STOREITEM_H
