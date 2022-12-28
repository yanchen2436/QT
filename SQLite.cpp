#include "SQLite.h"

void SQLController::SQLconnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //以“QSQLITE”为数据库类型，在本进程地址空间内创建一个SQLite数据库。
    db.setHostName("easybook-3313b0");      //设置数据库主机名
    db.setDatabaseName("qtDB.db");          //以上创建的数据库以“qtDB.db”为数据库名。它是SQLite在建立内存数据库时唯一可用的名字。
    db.setUserName("wang");             //设置数据库用户名
    db.setPassword("123456");                   //设置数据库密码
    db.open();
}

void SQLController::query(QString time1, QString time2)
{
    QString str = "SELECT count FROM stat where stat.time>=_time1 and stat.time<=_time2";
    str.replace("_time1", time1);
    str.replace("_time2", time2);
    exec(str);
}

void  SQLController::update(QString str)
{
    exec(str);
}

void SQLController::createTable(QString str)
{
    exec(str);
}

void SQLController::insert(QString group_name, int count)
{
    QString str = "INSERT TO rebar_count VALUES ( group_name, count)";
    str.replace("group_name", group_name);
    str.replace("count", QString::number(count));
    exec(str);
}

void SQLController::exec(QString str)
{
    queryExec.exec(str);
}
