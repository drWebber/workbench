#include "productconstructor.h"
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
#include <qsqlrecord.h>
#include <qevent.h>
#include <qdebug.h>
#include <qstring.h>

ProductConstructor::ProductConstructor(QList<QLabel *> &labels, QList<QLineEdit *> edits)
{
    this->labels = labels;
    this->edits = edits;
}

bool ProductConstructor::setProductPatterns(const QString &keyword)
{
    this->keyword = keyword;
    clearLabels();

    QSqlQuery query;
    query.prepare("SELECT * FROM patterns WHERE kid = (SELECT kid FROM keywords WHERE name = :name)");
    query.bindValue(":name", keyword);
    query.exec();
    QSqlRecord record = query.record();
    if (!query.next())
    {
        QMessageBox::warning(NULL, "Ошбика", "Шаблон подбора для ключа <b>" +
                             keyword.toUpper() + "</b> не найден!");
        return false;
    }

    int counter = 0;
    foreach (QLabel *label, labels) {
        int indx = record.indexOf("val" + QString::number(++counter));
        label->setText(query.value(indx).toString());
    }

    query.clear();
    return true;
}

void ProductConstructor::clearLabels()
{
    foreach (QLabel *label, labels) {
        label->setText("");
    }
}

QStringList ProductConstructor::getCompletions(const QString &sender)
{
    QString param = "param" + sender;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT " + param + " FROM `params` "
                  "WHERE kid = (SELECT `kid` FROM `keywords` "
                                "WHERE `name` = :name)");
    query.bindValue(":name", keyword);
    query.exec();

    QStringList result;
    while (query.next()) {
        result.append(query.value(0).toString());
    }
    return result;
}

bool ProductConstructor::eventFilter(QObject *watched, QEvent *event)
{
    //отслеживаем Ctrl+Space для полей ввода ProductConstructor
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        QString sender = watched->objectName().right(1);
        completer = new QCompleter(getCompletions(sender));
        if (keyEvent->key() == Qt::Key_Space) {
            if (keyEvent->modifiers().testFlag(Qt::ControlModifier)) {
                completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
                int id = sender.toInt()-1;
                edits[id]->setCompleter(completer);
                edits[id]->completer()->complete();
                return true;
            }
        } else if(keyEvent->key() == Qt::Key_R) {
            if(keyEvent->modifiers().testFlag(Qt::ControlModifier)){
                multChoice = new MultipleChoice(getCompletions(sender));
                multChoice->exec();
                return true;
            }
        }
    }
    return false;
}
