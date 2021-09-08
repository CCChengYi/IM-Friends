#include "signature.h"
#include "ui_signature.h"
#include "list.h"
#include "QMessageBox"


signature::signature(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signature)
{
    ui->setupUi(this);
    //隐藏系统边框
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
}

QString signature::si="";

signature::~signature()
{
    delete ui;
}

void signature::on_pushButton_clicked()
{
   si= ui->lineEdit->text();
   if(sqconn.savesignature(si)){
   QMessageBox::information(this,"提示","个性签名修改成功,下次登录时会显示!",QMessageBox::Ok);
   this->close();
   }
   else{
       QMessageBox::information(this,"警告","个性签名修改失败,请检查后重试!",QMessageBox::Ok);
   }

}

void signature::on_toolButton_clicked()
{
    close();
}
