#ifndef LIST_H
#define LIST_H

#include <QWidget>
#include <QMouseEvent>
#include <datadb.h>
namespace Ui {
class List;
}

class List : public QWidget
{
    Q_OBJECT
    QString username;

public:
    explicit List(QWidget *parent = nullptr);
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
    ~List();

private slots:
        void on_toolButton_clicked();

        void on_addfriends_clicked();

        void on_news_clicked();

        void on_pushButton_4_clicked();

        void on_toolButton_2_clicked();

        void on_pushButton_clicked();

        void on_pushButton_2_clicked();

        void on_pushButton_3_clicked();

        void on_pushButton_5_clicked();

        void on_pushButton_6_clicked();

        void on_pushButton_7_clicked();

private:
    Ui::List *ui;
    datadb sqconn;
public:
    static int buttonflag;
};

#endif // LIST_H
