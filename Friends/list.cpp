#include "list.h"
#include "ui_list.h"
#include "addfriends.h"
#include "chat.h"
#include "set.h"
#include "update.h"
#include "signature.h"
#include "widget.h"
#include "login.h"
#include <QDebug>

int List::buttonflag=0;
List::List(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::List)
{
    //显示ID
    ui->setupUi(this);
    qDebug()<<Login::data;
    sqconn.findFriends(Login::data);
    sqconn.findID(Login::data);
    QString id=sqconn.getname();
    ui->label_2->setText("ID:"+id);

    //显示头像
    sqconn.findpic(Login::data);
    QString picpath=sqconn.getpic();
    qDebug()<<"path"<<picpath;
    QSize idsize = ui->label_3->size();
    QPixmap idpixmap(":/"+picpath);
    idpixmap = idpixmap.scaled(idsize,Qt::IgnoreAspectRatio);
    ui->label_3->setPixmap(idpixmap);

    //显示好友列表
    ui->pushButton_2->setText(sqconn.getFriend(0));
    ui->pushButton_3->setText(sqconn.getFriend(1));
    ui->pushButton_5->setText(sqconn.getFriend(2));
    ui->pushButton_6->setText(sqconn.getFriend(3));
    ui->pushButton_7->setText(sqconn.getFriend(4));

    //隐藏系统边框
    this->setWindowFlags(Qt::SplashScreen|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

    //设置个性签名
    if(sqconn.getsignature()=="")
    ui->label_5->setText("请编辑你的个性签名");
    else
    ui->label_5->setText(sqconn.getsignature());


}

List::~List()
{
    delete ui;
}

void List::on_toolButton_clicked()
{
    this->close();
    QApplication *app;
    app->exit(0);
}

void List::on_addfriends_clicked()
{
    addfriends *add = new addfriends(this);
    add->show();
}

void List::on_news_clicked()
{
    Update *update = new Update;
    update->show();
}

void List::on_pushButton_4_clicked()
{
    Set *s = new Set;
    s->show();
}

void List::on_toolButton_2_clicked()
{
    signature* sign=new signature;
    sign->show();
}

void List::on_pushButton_clicked()
{
   buttonflag = 0;
    Widget *w=new Widget;
    w->show();

}

void List::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text()!="")
    {
        buttonflag=1;
        Widget *w=new Widget;
        w->show();
    }
}

void List::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text()!="")
    {
        buttonflag=1;
        Widget *w=new Widget;
        w->show();
    }
}

void List::on_pushButton_5_clicked()
{
    if(ui->pushButton_5->text()!="")
    {
        buttonflag=1;
        Widget *w=new Widget;
        w->show();
    }
}

void List::on_pushButton_6_clicked()
{
    if(ui->pushButton_6->text()!="")
    {
        buttonflag=1;
        Widget *w=new Widget;
        w->show();
    }
}

void List::on_pushButton_7_clicked()
{
    if(ui->pushButton_7->text()!="")
    {
        buttonflag=1;
        Widget *w=new Widget;
        w->show();
    }
}
