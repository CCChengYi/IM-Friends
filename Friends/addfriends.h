#ifndef ADDFRIENDS_H
#define ADDFRIENDS_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include"datadb.h"
#include "login.h"
#include "list.h"
namespace Ui {
class addfriends;
}

class addfriends : public QWidget
{
    Q_OBJECT
    QString username;
    QString email;

public:
    explicit addfriends(List *ll,QWidget *parent = nullptr);
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
    ~addfriends();
        void initsql();

private slots:
        void on_toolButton_clicked();

        QString getid();
        void setid(const QString &value);

        void on_pushButton_clicked();

        void on_toolButton_triggered(QAction *arg1);

private:
    Ui::addfriends *ui;
    datadb sqconn;
    List *ll;
};

#endif // ADDFRIENDS_H
