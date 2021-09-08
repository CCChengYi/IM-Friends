#include "datadb.h"
#include<QMessageBox>
#include<QDebug>
//#include<QNetworkAccessManager>
#include<QEventLoop>
//#include<QNetworkReply>
#include<QPixmap>
#include<QBitmap>
#include<QPainter>
#include"login.h"
//#include"globalobserver.h"


//构造函数中完成数据库的连接
datadb::datadb()
{
    //数据库驱动
    db=QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");//数据库服务器IP
    db.setUserName("root");//数据库用户名
    db.setPort(3306);//端口
    db.setPassword("123456");//密码
    db.setDatabaseName("friends");//使用哪个数据库

    //打开数据库
    if(!db.open())//打开失败
    {
        QMessageBox::warning(NULL,"error","open db error!",QMessageBox::Yes);
        //qDebug()<<QObject::tr("打开数据库失败");
    }
}


//登陆
bool datadb::login(QString &email, QString &password)
{

        QSqlQuery query;
        query.prepare("select email,password from user where email=:email and password=:password");

        query.bindValue(":email",email);
        query.bindValue(":password",password);
        query.exec();
        if(!query.next()){
            return false;
        }
        else{
            return true;
        }
}


//注册
bool datadb::user_register(QString &email, QString &id, QString &password, QString &pic)
{
    QSqlQuery query;
    query.prepare("select email from User where email=:email");
    query.bindValue(":email",email);
    query.exec();

    //用户已存在
    if(query.next())
    {
        return false;
    }
    else
    {
        query.prepare("insert into user(email,Name,Password,pic) values (:email,:id,:password,:pic)");
        query.bindValue(":email",email);
        query.bindValue(":id",id);
        query.bindValue(":password",password);
        query.bindValue(":pic",pic);
        //query.bindValue(":/Dajia-QQ/head/iconmonstr-generation-1-240.png",pic);
        query.exec();
        return true;
    }
}

void datadb::queryuserinfo(const QString &email)
{
    this->query.exec("select * from user");
    while(query.next())
    {
        if(email==(this->query.value("email").toString()))
        {
            this->email=this->query.value("email").toString();
            this->id=this->query.value("id").toString();
            this->password=this->query.value("password").toString();
        }
    }
}

void datadb::insertpic(const QString &pic)
{
    this->pic=pic;
    qDebug()<<"3"<<this->pic;
}

bool datadb::set(QString id, QString sex, QString school){
    QSqlQuery query,query1,query2;
    query.prepare("update user set school=:school where email=:email");
    query.bindValue(":school",school);
    query.bindValue(":email",Login::data);
    query.exec();

    query1.prepare("update user set sex=:sex where email=:email");
    query1.bindValue(":sex",sex);
    query1.bindValue(":email",Login::data);
    query1.exec();

    query2.prepare("update user set Name=:Name where email=:email");
    query2.bindValue(":Name",id);
    query2.bindValue(":email",Login::data);
    query2.exec();

    return true;
}

bool datadb::update(QString oldpassword, QString newpassword){
    QSqlQuery query;
    query.prepare("select * from user where email=:email and password=:oldpassword ");
    query.bindValue(":email",Login::data);
    query.bindValue(":oldpassword",oldpassword);
    query.exec();
    if(!query.next()){
        return false;
    }
    else{
        QSqlQuery query1;
        query1.prepare("update user set password=:newpassword where password=:oldpassword");
        query1.bindValue(":newpassword",newpassword);
        query1.bindValue(":oldpassword",oldpassword);
        query1.exec();
        return true;
    }


}

QString datadb::getport(){
    QSqlQuery query;
    query.prepare("select port from user where email=:email");
    query.bindValue(":email",Login::data);
    QString port;
    port=this->query.value("port").toString();
    return port;
}

bool datadb::savesignature(QString sign){
    QSqlQuery query;
    query.prepare("update user set signature=:signature where email=:email");
    query.bindValue(":signature",sign);
    query.bindValue(":email",Login::data);
    query.exec();
    return true;

}

void datadb::findFriends(QString &name){
    QSqlQuery query;
    query.exec("select * from friend");
    int i=0;
    while(query.next()){
        if((name == (query.value("email2").toString()))){

            this->friendlist[i] = query.value("email1").toString();

            ++i;
        }
        if((name == (query.value("email1").toString())))
        {
            this->friendlist[i] = query.value("email2").toString();

            ++i;
        }
    }
}


QString datadb::  getFriend(int i){
    return friendlist[i];
}


void datadb::findpic(QString &name)
{
    QSqlQuery query;
    query.exec("select * from user");
    query.exec();
    while(query.next())
    {
        if(name==(query.value("email").toString()))
        {
            this->pic=query.value("pic").toString();
            //qDebug()<<"dp1"<<pic;
        }
    }
}

QString datadb::getpic()
{
   // qDebug()<<"dp"<<pic;
    return pic;
}

QString datadb::getsignature(){
    QSqlQuery query;
    QString sign;
    query.exec("select * from user");

    int i=0;
    while(query.next()){
        if((Login::data == (query.value("email").toString()))){

           sign = query.value("signature").toString();

            ++i;
        }

    }
    return sign;
}
void datadb::findID(QString &name)
{
    QSqlQuery query;
    query.exec("select * from user");
    query.exec();
    while(query.next())
    {
        if(name==(query.value("email").toString()))
        {
            this->id=query.value("name").toString();

        }
    }
}

QString datadb::getname(){
    return id;
}
