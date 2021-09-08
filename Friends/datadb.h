#ifndef DATADB_H
#define DATADB_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QString>
#include<QPixmap>




class datadb
{
private:

    QSqlQuery query;        //查询操作

    static datadb* sqldb;
    QSqlDatabase db;

    QString id = "";
    QString email = "";
    QString password = "";
    QString pic="";
    QString friendlist[5]={"","","","",""};

public:
    explicit datadb();
    bool login(QString &str1,QString &str2);
    bool user_register(QString &email,QString &id,QString &password,QString &cpassword);
    void queryuserinfo(const QString &email);
    void insertpic(const QString &pic);
    bool set(QString id,QString sex,QString school);
    bool update(QString oldpassword,QString newpassword);
    QString getport();
    bool savesignature(QString sign);
    void findFriends(QString &name);
    QString  getFriend(int i);
    void findpic(QString &name);
    QString getpic();
    QString getsignature();
    void findID(QString &name);
    QString getname();
};

#endif // DATADB_H
