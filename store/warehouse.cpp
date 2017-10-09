#include "warehouse.h"
#include <qsqlquery.h>
#include <qvariant.h>
#define SMID 0
#define STORE_PLACE 1
#define MID 2
#define PATH 3
#define REG_EXP 4
#define LAST_PATH 5
#define START_ROW 6
#define ARTICLE_COL 7
#define ITEM_COUN_COLUMN 8

Warehouse::Warehouse()
{
}

Warehouse::Location Warehouse::getLocation() const
{
    return location;
}

void Warehouse::setLocation(const Location &value)
{
    location = value;
}

bool Warehouse::isValid(const Warehouse &w)
{
    return w.getSmid() > 0 ? true : false;
}

void Warehouse::setLastPath(const QString &value)
{
    lastPath = value;
}

void Warehouse::setRegExp(const QString &value)
{
    regExp = value;
}

void Warehouse::setPath(const QString &value)
{
    path = value;
}

void Warehouse::setItemCountCol(int value)
{
    itemCountCol = value;
}

void Warehouse::setArticleCol(int value)
{
    articleCol = value;
}

void Warehouse::setStartRow(int value)
{
    startRow = value;
}

void Warehouse::setMid(int value)
{
    mid = value;
}

void Warehouse::setSmid(int value)
{
    smid = value;
}

QString Warehouse::getLastPath() const
{
    return lastPath;
}

void Warehouse::load()
{
    QSqlQuery q;
    q.exec("SELECT * FROM `store_manufacturer`");
    while (q.next()) {
        Warehouse w;
        w.setSmid(q.value(SMID).toInt());
        Location loc = UNKNOWN;
        QString storePlace = q.value(STORE_PLACE).toString();
        if (storePlace == "Витебск") loc = VITEBSK;
        if (storePlace == "Минск") loc = MINSK;
        if (storePlace == "Внешнее") loc = OTHER;
        w.setLocation(loc);
        w.setMid(q.value(MID).toInt());
        w.setPath(q.value(PATH).toString());
        w.setRegExp(q.value(REG_EXP).toString());
        w.setLastPath(q.value(LAST_PATH).toString());
        w.setStartRow(q.value(START_ROW).toInt());
        w.setArticleCol(q.value(ARTICLE_COL).toInt());
        w.setItemCountCol(q.value(ITEM_COUN_COLUMN).toInt());
        whauses.append(w);
    }
}

Warehouse Warehouse::find(int mid, Warehouse::Location location)
{
    foreach (Warehouse w, whauses) {
        if (w.getMid() == mid && w.getLocation() == location) {
            return w;
        }
    }
    return Warehouse();
}

QString Warehouse::getRegExp() const
{
    return regExp;
}

QString Warehouse::getPath() const
{
    return path;
}

int Warehouse::getItemCountCol() const
{
    return itemCountCol;
}

int Warehouse::getArticleCol() const
{
    return articleCol;
}

int Warehouse::getStartRow() const
{
    return startRow;
}

int Warehouse::getMid() const
{
    return mid;
}

int Warehouse::getSmid() const
{
    return smid;
}
