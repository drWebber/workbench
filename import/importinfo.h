#ifndef IMPORTINFO_H
#define IMPORTINFO_H

#include <qstring.h>



class ImportInfo
{
public:
    ImportInfo();
    QString getMid();
    void setManufacturer(QString const &manufacturer);

    int getStartRow() const;
    void setStartRow(int value);

    int getArticleCol() const;
    void setArticleCol(int value);

    int getDescCol() const;
    void setDescCol(int value);

    int getUnitsCol() const;
    void setUnitsCol(int value);

    QString getFilePath() const;
    void setFilePath(const QString &value);

private:
    int mid, startRow, articleCol, descCol, unitsCol;
    QString filePath, manufacturer;
};

#endif // IMPORTINFO_H
