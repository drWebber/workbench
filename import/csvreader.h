#ifndef CSVREADER_H
#define CSVREADER_H

#include <qfile.h>
#include <qtextstream.h>

class CsvReader
{
public:
    CsvReader(QFile *csvFile, int startRow);
    QString readLine();
    bool atEnd();
    bool openCsv();
    void close();
private:
    QFile *csvFile;
    QTextStream *stream;
    int startRow;
};

#endif // CSVREADER_H
