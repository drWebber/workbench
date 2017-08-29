#include "nomenclaturetxtfile.h"
#include <qdir.h>

#include <qdebug.h>

NomenclatureTxtFile::NomenclatureTxtFile(const QFile &source)
{
    nomenclatureFile.setFileName(source.fileName() + ".txt");
    nomenclatureFile.open(QIODevice::ReadWrite | QIODevice::Text);
    nomOut = new QTextStream(&nomenclatureFile);

    multiplicyFile.setFileName(source.fileName() + ".mult.txt");
    multiplicyFile.open(QIODevice::ReadWrite | QIODevice::Text);
    multOut = new QTextStream(&multiplicyFile);
}

void NomenclatureTxtFile::appendNomenclature(const QString &row)
{
    *nomOut << row << endl;
}

void NomenclatureTxtFile::appendMultiplicy(const QString &row)
{
    *multOut << row << endl;;
}

void NomenclatureTxtFile::remove()
{
    nomOut->flush();
    multOut->flush();
    nomenclatureFile.close();
    multiplicyFile.close();
    nomenclatureFile.remove();
    multiplicyFile.remove();
}
