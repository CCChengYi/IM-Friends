#include "tcpserver.h"
#include "ui_tcpserver.h"
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
#include<QApplication>
#include<QTime>

TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer),localFile(nullptr),tcpServer(nullptr)
                         ,clientConnection(nullptr)
{
    ui->setupUi(this);
    tcpPort = 6666;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),
            this,SLOT(sendMessage()));
    initServer();
//服务端通过信号 SIGNAL:newConnection() 来判断是否接收到了新的连接
//当服务端接收到一个客户端的连接时，就会触发信号newConnection()，此时调用相应的槽函数,保存新接收到的连接
}
//服务器：申请套接字 -> 绑定套接字 -> 监听套接字 -> 接收连接 -> 开始发送数据接收数据
TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::initServer()
{//初始化
    payloadSize = 64 * 1024;
    TotalBytes = 0;
    bytestoWrite = 0;
    bytesWritten = 0;
    ui->serverStatusLabel->setText(tr("请选择要传送的文件"));
    ui->progressBar->reset();
    ui->serverOpenBtn->setEnabled(true);
    ui->serverSendBtn->setEnabled(false);
    tcpServer->close();
    //localFile = new QFile(fileName);

}


void TcpServer::sendMessage()
{
    qDebug () << "TCP的链接已建立" ;
    ui->serverSendBtn->setEnabled(false);
    clientConnection = tcpServer->nextPendingConnection();//nextPendingConnection()函数获得连接客户端的SOCKET套接字
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),
            this,SLOT(updateClientProgress(qint64)));
    ui->serverStatusLabel->setText(tr("开始传送文件:\n %1!").arg(theFileName));

    localFile = new QFile(fileName);
    if(! localFile->open(QFile::ReadOnly))// //打开文件准备读取数据发送
    {
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2").arg(fileName)
                             .arg(localFile->errorString()));
        return ;
    }

    TotalBytes = localFile->size();

    time.start();
    //把outblock空间与数据流绑定
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_0);
    time.start();//读取数据流的时候计算时间

    QString currentFile = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) <<qint64(0) <<currentFile;


    TotalBytes +=outBlock.size();
    sendOut.device()->seek(0);

    sendOut << TotalBytes << qint64((outBlock.size() - sizeof(qint64)*2));


    bytestoWrite = TotalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);


}

void TcpServer::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten +=(int) numBytes;
    if(bytestoWrite > 0)//数据还未读取完时
    {
        outBlock = localFile->read(qMin(bytestoWrite,payloadSize));//读取一段内容
        bytestoWrite -=(int)clientConnection->write(outBlock);
        outBlock.resize(0);

    }
    else
    {
        localFile->close();
    }

    //设置进度条最大值
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
   // qDebug() << "uerTime:" << useTime;
    double speed = bytesWritten / useTime;
    ui->serverStatusLabel->setText(tr("已发送 %1MB( %2MB/s)"
                                      "\n共%3MB 已用时:%4秒\n估计剩余时间:%5秒")
                                   .arg(bytesWritten / (1024*1024))
                                   .arg(speed * 1000 /(1024*1024),0,'f',2)
                                   .arg(TotalBytes /(1024*1024))
                                   .arg(useTime/1000,0,'f',0)
                                   .arg(TotalBytes/speed/1000 - useTime/1000,0,'f',0));
    if(bytesWritten == TotalBytes)//传输完成
    {
        localFile->close();
        tcpServer->close();
        ui->serverStatusLabel->setText(tr("传送文件: %1成功").arg(theFileName));

    }

}




void TcpServer::on_serverOpenBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
       // qDebug() << "文件名" <<  theFileName ;
        ui->serverStatusLabel->setText(tr("要发送的文件为:%1").arg(theFileName));
        ui->serverSendBtn->setEnabled(true);
        ui->serverOpenBtn->setEnabled(false);


    }
  //  localFile = new QFile(fileName);



}

//监听
void TcpServer::on_serverSendBtn_clicked()
{
    if(! tcpServer->listen(QHostAddress::Any,tcpPort))
    {
        qDebug() << tcpServer->errorString()<<"ni好吧";
        close();
        return ;
    }
    ui->serverSendBtn->setEnabled(false);
    ui->serverStatusLabel->setText(tr("等待对方的接受......"));

    emit sendFileName(theFileName);

}
void TcpServer::on_serverCloseBtn_clicked()
{
    //qDebug() << "关闭" ;
    if(tcpServer->isListening())
    {
        qDebug() << "点击了关闭按钮";
        tcpServer->close();
        if(localFile->isOpen())
        {
            localFile->close();
        }
        clientConnection->abort();

    }
    close();
    ui->~TcpServer();

}

void TcpServer::refused()
{
    tcpServer->close();
    ui->serverStatusLabel->setText(tr("对方拒绝接受!!!"));


    //qDebug() <<  ;

}

void TcpServer::closeEvent(QCloseEvent *)
{
    //qDebug() << "退出了server";
    on_serverCloseBtn_clicked();
}















