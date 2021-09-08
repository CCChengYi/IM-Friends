#include "widget.h"
#include <QApplication>
#include<QTextCodec>
#include<QIcon>
#include "login.h"
#include "list.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    /*Widget w;
    w.setWindowIcon(QIcon(":/myicon.ico"));
    w.setWindowTitle("局域网聊天");
    w.show();*/

   Login *l = new Login;
   l->show();

   /*List *list = new List;
    list->show();*/




    return a.exec();
}
