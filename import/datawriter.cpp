#include "datawriter.h"
#include <qfileinfo.h>

#include <qmessagebox.h>
#include <qdebug.h>

DataWriter::DataWriter(QString tmpFileName)
{
    file.setFileName(tmpFileName);
    if (file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text)) {
        stream = new QTextStream(&file);
        stream->setCodec("UTF-8");
    } else {
        QMessageBox::critical(NULL, "Ошибка создания файла", file.fileName());
    }
    qDebug() << QFileInfo(file).absoluteFilePath();
}

DataWriter::~DataWriter()
{
    stream->flush();
//    file.remove();
}

void DataWriter::append(QString line)
{
    *stream << line << '\n';
}

QString DataWriter::getFilePath()
{
    return QFileInfo(file).absoluteFilePath();
}
