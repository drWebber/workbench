#include "nomenclaturetxtfile.h"
#include <qdir.h>

#include <qdebug.h>

DataWriter::DataWriter(const QFile &source)
{
    nomenclatureFile.setFileName(source.fileName() + ".txt");
    nomenclatureFile.open(QIODevice::ReadWrite | QIODevice::Text);
    nomOut = new QTextStream(&nomenclatureFile);

    multiplicyFile.setFileName(source.fileName() + ".mult.txt");
    multiplicyFile.open(QIODevice::ReadWrite | QIODevice::Text);
    multOut = new QTextStream(&multiplicyFile);
}

void DataWriter::appendNomenclatureRow(const QString &row)
{
    *nomOut << row << endl;
}

void DataWriter::appendMultiplicyRow(const QString &row)
{
    *multOut << row << endl;;
}

void DataWriter::closeFiles()
{
    nomenclatureFile.close();
    multiplicyFile.close();
}
