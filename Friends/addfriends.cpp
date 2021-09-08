#include "addfriends.h"
#include "ui_addfriends.h"
#include "QAction"

#include <QStackedWidget>
#include <QMessageBox>
#include <QDebug>
#include <list.h>
addfriends::addfriends(List* ll,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addfriends)
{
    ui->setupUi(this);
    //隐藏系统边框
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

    this->setid(username);
    this->ll=ll;
    //search
    QAction * searchAction = new QAction(ui->lineEdit);
    searchAction->setIcon(QIcon("://pic/icon2/iconmonstr-search-thin-240.png"));
    ui->lineEdit->addAction(searchAction,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。

}

addfriends::~addfriends()
{
    delete ui;
}

void addfriends::on_toolButton_clicked()
{
    this->close();
}

void addfriends::on_pushButton_clicked()
{
    QString email = ui->lineEdit->text();

    QSqlQuery query;
    query.prepare("select email from User where email=:email");
    query.bindValue(":email",email);
    query.exec();

    if(!query.next()){
        QMessageBox::information(this,"警告","该用户不存在!",QMessageBox::Ok);

    }
    else{
        QSqlQuery query1;
        query1.prepare("select * from friend where email1=:email and email2=:username"
                       "Union"
                       "select * from friend where email1=:username and email2=:email");

        query1.bindValue(":email",email);
        query1.bindValue(":username",Login::data);

        //qDebug() << username;

        query1.exec();
        if(query1.next()){
        QMessageBox::information(this,"警告","你与该用户已成为好友!",QMessageBox::Ok);
        }
       else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,tr("提示"),"你确定要添加该用户为好友吗?",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply == QMessageBox::Yes){
            //插入朋友表
            //qDebug() << email << " " << username;
            QSqlQuery query2;
            query2.prepare("insert into friend(email1,email2) values(:email,:username)");
            query2.bindValue(":email",email);
            query2.bindValue(":username",Login::data);

            query2.exec();
            QMessageBox::information(this,"提示","添加成功!",QMessageBox::Ok);
            this->ll->~List();
            List *l =new List;
            l->show();
       }
   }
    }
    this->close();
}

QString addfriends::getid()
{
    return email;
}


void addfriends::setid(const QString &value)
{
    username=value;
}
