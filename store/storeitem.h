#ifndef STOREITEM_H
#define STOREITEM_H

#include "store/newproduct.h"
#include <qlist.h>


class StoreItem : public NewProduct
{
public:
    StoreItem();
    enum Location {VITEBSK, MINSK, OTHER} location;
    int getAvailability(Location location) const;
    void setAvailability(Location location, int count);
private:
    QList<int> availability;
};

#endif // STOREITEM_H
