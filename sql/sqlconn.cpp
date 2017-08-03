#include "sql/sqlconn.h"

SqlConn::SqlConn()
{
}


SqlConn::~SqlConn()
{
}

void SqlConn::connect()
{
    db = QSqlDatabase::addDatabase("QMYSQL3");

    db.setHostName("localhost");
    db.setDatabaseName("nordelectro");
    db.setUserName("root");
//    db.setPassword("by3CVUTCN04oYS1H");

    if (!db.open()){
        QMessageBox::critical(NULL, "Ошибка", db.lastError().text());
        qDebug() << db.lastError().text();
    }
}

bool SqlConn::isConnected()
{
    return db.isOpen() ? true : false;
}
