#ifndef SET_H
#define SET_H

#include <QWidget>
#include <QMouseEvent>
#include "datadb.h"

namespace Ui {
class Set;
}

class Set : public QWidget
{
    Q_OBJECT

public:
    explicit Set(QWidget *parent = nullptr);
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
    ~Set();

private slots:
        void on_toolButton_clicked();

        void on_pushButton_clicked();

private:
    Ui::Set *ui;
    datadb sqconn;
};

#endif // SET_H
