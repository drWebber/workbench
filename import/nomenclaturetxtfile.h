#ifndef NOMENCLATUREINFILE_H
#define NOMENCLATUREINFILE_H

#include <qfile.h>
#include <qtextstream.h>


class NomenclatureTxtFile
{
public:
    NomenclatureTxtFile(const QFile &source);
    void appendNomenclature(const QString &row);
    void appendMultiplicy(const QString &row);
    void remove();
private:
    QFile nomenclatureFile;
    QFile multiplicyFile;
    QTextStream *nomOut;
    QTextStream *multOut;
};

#endif // NOMENCLATUREINFILE_H
