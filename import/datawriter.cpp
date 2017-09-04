#include "datawriter.h"

#include <qfileinfo.h>

DataWriter::DataWriter(QString tmpFileName)
{
    file.setFileName(tmpFileName);
    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text)) {
        stream = new QTextStream(&file);
    }
}

DataWriter::~DataWriter()
{
    stream->flush();
}

void DataWriter::append(QString line)
{
    *stream << line << '\n';
}

void DataWriter::removeFile()
{
    file.remove();
}

QString DataWriter::getFilePath()
{
    return QFileInfo(file).absolutePath();
}
