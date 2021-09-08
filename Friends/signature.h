#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <QWidget>
#include <QMouseEvent>
#include <datadb.h>

namespace Ui {
class signature;
}

class signature : public QWidget
{
    Q_OBJECT

public:
    explicit signature(QWidget *parent = nullptr);
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
    ~signature();

public:
    static QString si;

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::signature *ui;
    datadb sqconn;
};

#endif // SIGNATURE_H
