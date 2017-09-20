#include "csvreader.h"

#include <qdebug.h>

CsvReader::CsvReader(QFile *csvFile, int startRow)
{
    this->csvFile = csvFile;
    this->startRow = startRow;
}

CsvReader::~CsvReader()
{
    csvFile->close();
    csvFile->remove();
}

QString CsvReader::readLine()
{
    QString line;
    /* в ячейках экселя могут быть забиты переводы на новую
     строку '\n' - соответственно поток видит в такой ситуации 2 и более строк,
     вместо одной. Если встречаем этот случай - продолжаем читать сроки,
     пока они не закончатся ';' */
    while (line.isEmpty() || line.contains(QRegExp("\\.$"))) {
        if (line.contains(QRegExp("\\.$"))) {
            line.append(" ");
        }
        line.append(stream->readLine());
    }
    return line;
}

bool CsvReader::atEnd()
{
    return stream->atEnd() ? true : false;
}

bool CsvReader::openCsv()
{
    if (csvFile->open(QFile::ReadOnly | QFile::Text)) {
        stream = new QTextStream(csvFile);
        for (int i = 0; i < startRow; ++i) stream->readLine();
        return true;
    } else {
        return false;
    }
}
