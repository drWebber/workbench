#include "xlsreader.h"
#include <qdir.h>
#include <dshow.h>
#define xlCSV 6
#include <qdebug.h>

XlsReader::XlsReader(QFile *xlsFile)
{
    this->xlsFile = xlsFile;
    CoInitialize(0);
    excel = new QAxObject("Excel.Application", NULL);
    xlsFileInfo = QFileInfo(*this->xlsFile);
}

void XlsReader::openActiveWorkBook()
{
    if (xlsFile->exists()) {
       workbooks = excel->querySubObject("WorkBooks");
       workbooks->dynamicCall("Open (const QString&)", xlsFileInfo.absoluteFilePath());

       workbook = excel->querySubObject("ActiveWorkBook");
    }

}

void XlsReader::close()
{
    excel->setProperty("DisplayAlerts", false);
    workbook->dynamicCall("Close (Boolean)", true);
    excel->dynamicCall("Quit (void)");
    delete workbook;
    delete workbooks;
}

QFile *XlsReader::saveAsCsv()
{
    QDir::setCurrent(xlsFileInfo.absoluteDir().path());
    QFile *csvFile = new QFile(xlsFileInfo.fileName() + ".csv");
    workbook->dynamicCall("SaveAs (const QString&, const int&)",
                          QFileInfo(*csvFile).absoluteFilePath().replace("/", "\\"), xlCSV);
    return csvFile;
}
