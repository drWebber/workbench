#ifndef CLIPBOARDWORKER_H
#define CLIPBOARDWORKER_H

#include <qclipboard.h>
#include <qvector.h>
#include <qregularexpression.h>

class ClipboardWorker
{
public:
    ClipboardWorker();
    QVector<QVector<QString> > lastTable() const;
    QVector<QVector<QString> > getTable();
    bool isTable();

private:
    QVector<QVector<QString> > table;
    QString clipboardText;
};

#endif // CLIPBOARDWORKER_H
