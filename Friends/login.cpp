#include "login.h"
#include "ui_login.h"
#include "register.h"
#include "QAction"
#include "list.h"
#include <qmessagebox.h>
#include <QStackedWidget>
#include <QMessageBox>
#include <QDebug>
#include <QWidget>

QString Login::data="";

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //隐藏系统边框
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

    //e-mail文本框
    QAction * searchAction = new QAction(ui->lineEdit);
    searchAction->setIcon(QIcon("://pic/iconmonstr-email-2-240.png"));
    ui->lineEdit->addAction(searchAction,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    //密码文本框
    QAction * searchAction_2 = new QAction(ui->lineEdit);
    searchAction_2->setIcon(QIcon("://pic/iconmonstr-keyboard-2-240.png"));
    ui->lineEdit_2->addAction(searchAction_2,QLineEdit::TrailingPosition);//表示action所在方位（右侧）。
    QAction * searchAction_3 = new QAction(ui->lineEdit);
    searchAction_3->setIcon(QIcon("://pic/iconmonstr-lock-4-240.png"));
    ui->lineEdit_2->addAction(searchAction_3,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
}

Login::~Login()
{
    delete ui;
}

void Login::on_toolButton_clicked()
{
    this->close();
    QApplication *app;
    app->exit(0);
}

void Login::on_Register_clicked()
{
    Register *r = new Register;
    r->show();
    this->close();
}

void Login::on_pushButton_2_clicked()
{
    //获取email和密码
    QString email = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();


    if(email == ""||password==""){
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    }
    else{
        if(sqconn.login(email,password))
        {
            QMessageBox::information(this,"提醒","登录成功!",QMessageBox::Ok);
           data=email;
            List* newlist=new List();


            newlist->show();
            this->close();
        }
        else {
            QMessageBox::information(this,"警告","email或密码错误!",QMessageBox::Ok);
        }
    }
}
