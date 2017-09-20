#ifndef DATAPARCER_H
#define DATAPARCER_H

#include <qlist.h>



class DataParcer
{
public:
    DataParcer(const QList<int> &columns);
    QString parceLine(QString line);
private:
    QList<int> columns;
    void replaceLine(QString &line, QString &replacePatt);
};

#endif // DATAPARCER_H
