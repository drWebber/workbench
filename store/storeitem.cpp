#include "storeitem.h"

StoreItem::StoreItem() : NewProduct()
{

}

int StoreItem::getAvailability(Location location) const
{
    return availability.at(location);
}

void StoreItem::setAvailability(Location location, int count)
{
    availability[location] = count;
}
