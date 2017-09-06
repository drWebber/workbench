#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <qfile.h>
#include <qtextstream.h>



class DataWriter
{
public:
    DataWriter(QString tmpFileName);
    ~DataWriter();
    QString getFilePath();
    void append(QString line);
private:
    QFile file;
    QTextStream *stream;
};

#endif // DATAWRITER_H
