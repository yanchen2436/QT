#ifndef SQLITE_H
#define SQLITE_H
#include <QCoreApplication>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

class SQLController
{
private:
    QSqlQuery queryExec;
    static SQLController *sqlcontroller;

    SQLController();

    SQLController(QString dataBaseName);
public:


    static SQLController *getSQLController(QString dataBaseName);

    void query(QString time1, QString time2);

    void del(QString str);

    void insert(QString group_name, int count);

    void update(QString str);

    void createTable(QString str);

    void createSQL(QString str);

    void exec(QString str);
};



#endif // SQLITE_H
