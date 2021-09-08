#include "update.h"
#include "ui_update.h"
#include <QMessageBox>

Update::Update(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Update)
{
    ui->setupUi(this);
    //隐藏系统边框
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

}

Update::~Update()
{
    delete ui;
}

void Update::on_toolButton_clicked()
{
    this->close();
}

void Update::on_pushButton_clicked()
{
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();
    QString str3=ui->lineEdit_3->text();
    if(str2!=str3){
        QMessageBox::information(this,"警告","两次输入的新密码不一致!",QMessageBox::Ok);
    }
    else{
        if(!sqconn.update(str1,str2)){
            QMessageBox::information(this,"警告","输入的旧密码错误!",QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this,"提示","修改成功!",QMessageBox::Ok);
        }
    }
}
