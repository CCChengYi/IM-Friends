#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include<QUdpSocket>
#include<QTcpServer>
#include"tcpclient.h"
#include"tcpserver.h"
#include<QColor>
#include<QKeyEvent>
#include"chat.h"
#include <QLabel>
namespace Ui {
class Widget;
}

//枚举变量信息类型,分别为消息,新加入者,用户退出,文件名,拒绝接受文件


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
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
    ~Widget();
protected:
    void newParticipant(QString userName,QString localHostName,QString ipAddress);

    void leftParticipant(QString userName,QString localHostName,QString time);

    void sendMessage(messageType type,QString serverAddress = "");

    QString getIP();

    QString getUserName();

    QString getMessage();

    void hasPendingFile(QString userName,QString  serverAddress,
                        QString clientAddress,QString fileName);
    bool saveFile(const QString &fileName);

    void closeEvent(QCloseEvent *e);

   // void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

    void showXchat(QString localHostName,QString ipAddress);


private slots:
    void processPendingDatagrams();

    void getFileName(QString);


    void on_sendPushButton_clicked();

    void on_exitPushButton_clicked();

    void on_sendToolBtn_clicked();

    void on_fontComBox_currentFontChanged(const QFont &f);

    void on_sizeComboBox_currentIndexChanged(const QString &arg1);

    void on_boldToolBtn_clicked(bool checked);

    void on_italicToolBtn_clicked(bool checked);

    void on_underlineToolBtn_clicked(bool checked);

    void on_colorToolBtn_clicked();

    void on_saveToolBtn_clicked();

    void on_clearToolBtn_clicked();

    void on_userTableWidget_doubleClicked(const QModelIndex &index);

    void on_toolButton_clicked();
    void on_toolButton_triggered(QAction *arg1);


private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket;
    qint16 port;

    QString fileName;
    TcpServer *server;
    QColor color;

    Chat *privateChat;
    Chat *privateChat1;


    static int count,count2;


};

#endif // WIDGET_H
