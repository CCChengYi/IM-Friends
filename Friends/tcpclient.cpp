#include "tcpclient.h"
#include "ui_tcpclient.h"
#include<QHostInfo>
#include<QMessageBox>
#include<QDateTime>
#include<QProcess>
#include<QDataStream>
#include<QScrollBar>
#include<QFont>
#include<QNetworkInterface>
#include<QStringList>
#include<QDebug>

TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    tcpClient(nullptr),
    localFile(nullptr),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);



    TotalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    tcpClient = new QTcpSocket(this);
    tcpPort = 6666;
    connect(tcpClient,SIGNAL(readyRead()),//当客户端向服务端成功发送数据之后，就会在服务端触发readyRead()信号，此时通过调用相应的自定义的槽函数保存接收到的数据；
            this,SLOT(readMessage()));//通过connect函数建立信号readyRead()与槽函数readMessage()的连接
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

}
//客户端：申请套接字 -> 建立连接 -> 发送数据 和 接收数据
TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::setFileName(QString fileName)
{
    localFile = new QFile(fileName);
}

void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();

}

//客户端通过IP和PORT连接服务端，当成功建立连接之后，就可进行数据的收发
void TcpClient::newConnect()
{

    blockSize = 0;
    tcpClient->abort();//重置socket，丢弃写入缓冲区的任何数据
    tcpClient->connectToHost(hostAddress,tcpPort);
    time.start();

}

void TcpClient::readMessage()
{
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_0);//将数据序列格式化为对应qt版本

    float useTime = time.elapsed();

    if(bytesReceived <= sizeof(qint64)*2)
    {
        if((tcpClient->bytesAvailable() >= sizeof(qint64)*2) && (fileNameSize ==0))//根据文件大小判断是否是第一次读取数据
        {
            in >> TotalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((tcpClient->bytesAvailable() >= fileNameSize) && (fileNameSize!=0))
        {
            in >> fileName;
            bytesReceived += fileNameSize;
            if(! localFile->open(QFile::WriteOnly))
            {
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2.")
                                     .arg(fileName)
                                     .arg(localFile->errorString()));
                return ;
            }
            else return ;

        }


    }
    if(bytesReceived < TotalBytes)
    {
        bytesReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);

    }

    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->tcpClientStatusLabel->setText(tr("已接收 %1MB( %2MB/s)"
                                         "\n共%3MB 已用时:%4秒\n估计剩余时间:%5秒")
                                      .arg(bytesReceived / (1024*1024))
                                      .arg(speed *1000/(1024*1024),0,'f',2)
                                      .arg(TotalBytes / (1024*1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(TotalBytes/speed/1000 - useTime/1000,0,'f',0 ));
    if(bytesReceived == TotalBytes)
    {
       localFile ->close();
       tcpClient->close();
       ui->tcpClientStatusLabel->setText(tr("接收文件: %1完毕").arg(fileName));

    }


}

void TcpClient::displayError(QAbstractSocket::SocketError  sockError)
{
    switch (sockError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    default:
        qDebug() << tcpClient->errorString();
    }



}


void TcpClient::on_tcpClientCancleBtn_clicked()
{
    tcpClient->abort();
   if(localFile->isOpen())
    {
        localFile->close();
    }
    close();
    ui->~TcpClient();

}

void TcpClient::on_tcpClientCloseBtn_clicked()
{
   on_tcpClientCancleBtn_clicked();

}


void TcpClient::closeEvent(QCloseEvent *)
{
    on_tcpClientCloseBtn_clicked();
}
