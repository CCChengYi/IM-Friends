#include "register.h"
#include "ui_register.h"
#include "QAction"
#include "login.h"
#include"datadb.h"

#include <QStackedWidget>
#include <QMessageBox>
#include <QDebug>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    //e-mail文本框
    QAction * searchAction = new QAction(ui->lineEdit);
    searchAction->setIcon(QIcon("://pic/iconmonstr-email-2-240.png"));
    ui->lineEdit->addAction(searchAction,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    //ID
    QAction * searchAction_2 = new QAction(ui->lineEdit);
    searchAction_2->setIcon(QIcon("://pic/iconmonstr-smiley-7-240.png"));
    ui->lineEdit_2->addAction(searchAction_2,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    //密码文本框
    QAction * searchAction_3 = new QAction(ui->lineEdit);
    searchAction_3->setIcon(QIcon("://pic/iconmonstr-keyboard-2-240.png"));
    ui->lineEdit_3->addAction(searchAction_3,QLineEdit::TrailingPosition);//表示action所在方位（右侧）。
    QAction * searchAction_4 = new QAction(ui->lineEdit);
    searchAction_4->setIcon(QIcon("://pic/iconmonstr-lock-4-240.png"));
    ui->lineEdit_3->addAction(searchAction_4,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    //确认密码文本框
    QAction * searchAction_5 = new QAction(ui->lineEdit);
    searchAction_5->setIcon(QIcon("://pic/iconmonstr-keyboard-2-240.png"));
    ui->lineEdit_4->addAction(searchAction_5,QLineEdit::TrailingPosition);//表示action所在方位（右侧）。
    QAction * searchAction_6 = new QAction(ui->lineEdit);
    searchAction_6->setIcon(QIcon("://pic/iconmonstr-lock-4-240.png"));
    ui->lineEdit_4->addAction(searchAction_6,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
}

Register::~Register()
{
    delete ui;
}

void Register::on_toolButton_clicked()
{
    this->close();
}

void Register::on_pushButton_clicked()
{
    QString email = ui->lineEdit->text();
    QString id = ui->lineEdit_2->text();
    QString password = ui->lineEdit_3->text();
    QString cpassword = ui->lineEdit_4->text();

    QString pic=this->pic;

    if(password!=cpassword)
    {
        QMessageBox::information(this,"警告","两次输入的密码不一致!",QMessageBox::Ok);
    }
    else if(sqconn.user_register(email,id,password,pic))
    {
        QMessageBox::information(this,"警告","注册成功!",QMessageBox::Ok);

        Login* login = new Login;
                login->show();
                this->close();
    }
    else {
        QMessageBox::information(this,"警告","用户已存在!",QMessageBox::Ok);
    }

}

void Register::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->currentIndex()==0)
    {
        qDebug()<<"0";
        this->pic="pic/head/iconmonstr-generation-1-240.png";
    }
    else if(ui->comboBox->currentIndex()==1)
    {
        qDebug()<<"1";
        this->pic="pic/head/iconmonstr-generation-12-240.png";
    }
    else if(ui->comboBox->currentIndex()==2)
    {
        this->pic="pic/head/iconmonstr-generation-13-240.png";
        qDebug()<<"2";
    }
    else if(ui->comboBox->currentIndex()==3)
    {
        qDebug()<<"3";
        this->pic="pic/head/iconmonstr-generation-14-240.png";
    }
    else if(ui->comboBox->currentIndex()==4)
    {
        qDebug()<<"4";
        this->pic="pic/head/iconmonstr-generation-15-240.png";
    }
    else if(ui->comboBox->currentIndex()==5)
    {
        qDebug()<<"5";
        this->pic="pic/head/iconmonstr-generation-2-240.png";
    }
    else if(ui->comboBox->currentIndex()==6)
    {
        qDebug()<<"6";
        this->pic="pic/head/iconmonstr-generation-16-240.png";
    }
}
