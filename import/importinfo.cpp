#include "importinfo.h"
#include <qsqlquery.h>
#include <qvariant.h>

ImportInfo::ImportInfo()
{

}

int ImportInfo::getMid()
{
    mid = -1;
    QSqlQuery query = QSqlQuery("SELECT mid FROM manufacturers WHERE name = '" + manufacturer + "'");
    query.exec();
    if (query.next()) {
        mid = query.value(0).toInt();
    }
    return mid;
}

void ImportInfo::setManufacturer(const QString &manufacturer)
{
    this->manufacturer = manufacturer;
}

int ImportInfo::getStartRow() const
{
    return startRow;
}

void ImportInfo::setStartRow(int value)
{
    startRow = value;
}

int ImportInfo::getArticleCol() const
{
    return articleCol;
}

void ImportInfo::setArticleCol(int value)
{
    articleCol = value;
}

int ImportInfo::getDescCol() const
{
    return descCol;
}

void ImportInfo::setDescCol(int value)
{
    descCol = value;
}

int ImportInfo::getUnitsCol() const
{
    return unitsCol;
}

void ImportInfo::setUnitsCol(int value)
{
    unitsCol = value;
}

QString ImportInfo::getFilePath() const
{
    return filePath;
}

void ImportInfo::setFilePath(const QString &value)
{
    filePath = value;
}
