#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include"datadb.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
    QString username;

public:
    explicit Login(QWidget *parent = nullptr);
    bool isPressedWidget;
     QPoint last;
        void mousePressEvent(QMouseEvent *event)//鼠标点击
        {
            isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
            last = event->globalPos();
        }
        void mouseMoveEvent(QMouseEvent *event)//鼠标移动
        {
            if (isPressedWidget)
                {
                    int dx = event->globalX() - last.x();
                    int dy = event->globalY() - last.y();
                    last = event->globalPos();
                    move(x()+dx, y()+dy);
                }
        }
        void mouseReleaseEvent(QMouseEvent *event)//鼠标释放
        {
            int dx = event->globalX() - last.x();
            int dy = event->globalY() - last.y();
            move(x()+dx, y()+dy);
            isPressedWidget = false; // 鼠标松开时，置为false
        }
    ~Login();

        void initsql(); //初始化数据库

public:
        static QString data;

private slots:
    void on_toolButton_clicked();

    void on_Register_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Login *ui;

    //获取基本信息
    datadb sqconn;//连接到数据库
};

#endif // LOGIN_H
