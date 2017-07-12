#ifndef SQLCONN_H
#define SQLCONN_H
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqlerror.h>
#include <qdebug.h>
#include <qmessagebox.h>

class SqlConn
{
public:
    SqlConn();
    ~SqlConn();
    void connect();
    bool isConnected();
private:
    QSqlDatabase db;
};

#endif // SQLCONN_H
