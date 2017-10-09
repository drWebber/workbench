#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <qlist.h>
#include <qstring.h>

class Warehouse
{
public:
    Warehouse();
    enum Location {VITEBSK, MINSK, OTHER, UNKNOWN};
    int smid = -1;
    int mid, startRow, articleCol, itemCountCol;
    Location location;
    QString path,  regExp, lastPath;
    QList<Warehouse> whauses;

    int getSmid() const;
    Warehouse::Location getLocation() const;
    int getMid() const;
    int getStartRow() const;
    int getArticleCol() const;
    int getItemCountCol() const;
    QString getPath() const;
    QString getRegExp() const;
    QString getLastPath() const;
    void load();
    Warehouse find(int mid, Location location);
    bool isValid(const Warehouse &w);
private:
    void setSmid(int value);
    void setLocation(const Location &value);
    void setMid(int value);
    void setStartRow(int value);
    void setArticleCol(int value);
    void setItemCountCol(int value);
    void setPath(const QString &value);
    void setRegExp(const QString &value);
    void setLastPath(const QString &value);
};

#endif // WAREHOUSE_H
