#ifndef NOMENCLATUREINFILE_H
#define NOMENCLATUREINFILE_H

#include <qfile.h>
#include <qtextstream.h>


class DataWriter
{
public:
    DataWriter(const QFile &source);
    void appendNomenclatureRow(const QString &row);
    void appendMultiplicyRow(const QString &row);
    void closeFiles();
private:
    QFile nomenclatureFile;
    QFile multiplicyFile;
    QTextStream *nomOut;
    QTextStream *multOut;
};

#endif // NOMENCLATUREINFILE_H
