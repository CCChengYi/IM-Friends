#include "set.h"
#include "ui_set.h"
#include<QMessageBox>

Set::Set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
    //隐藏系统边框
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

}

Set::~Set()
{
    delete ui;
}

void Set::on_toolButton_clicked()
{
    this->close();
}

void Set::on_pushButton_clicked()
{
    if(sqconn.set(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text())){
        QMessageBox::information(this,"提示","修改成功!",QMessageBox::Ok);
        this->close();
    }
    else{
        QMessageBox::information(this,"警告","修改失败,请检查后重试!",QMessageBox::Ok);
    }
}
