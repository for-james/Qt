#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/11.png").scaled(this->size())));
    this->setPalette(palette);

    socket=new QTcpSocket(this);
}

Widget::~Widget()
{
    delete ui;
}
//mdoe 1 2 3    1位温湿度2位距离    3为全部
void mycpy(char *a,char* b,int mode){
    char Tdata[4];
    char Hdata[4];
    char disdata[7];
    for(int i=0;i<3;++i){
        Tdata[i]=b[i];
        Hdata[i]=b[i+3];
    }
    Hdata[3]='\0';
    Tdata[3]='\0';
    for(int i=6,j=0;i<6;++i,++j){
        disdata[j]=b[i];
    }
     disdata[6]='\0';
    if(mode==1||mode==3){
        if(Tdata[0]=='#'){
            strcpy(a,"温湿度：#");
        }else{
             strcpy(a,"温度：");
             strcat(a,Tdata);
             strcat(a,"  ");
             strcat(a,"湿度：");
             strcat(a,Hdata);
        }
    }
    if(mode==3){
        strcat(a,"    ");
    }
    if(mode==2||mode==3){
        if(disdata[0]=='#'){
            strcpy(a,"节点距离：#");
        }else{
             strcpy(a,"节点距离：");
             strcat(a,disdata);
             strcat(a,"cm");
        }
    }
}

void Widget::on_action1_clicked()
{
    if(socket->state()==QAbstractSocket::ConnectedState){
        socket->write("1");

        QByteArray msg = socket->readAll();
        int size = msg.size();
        char msg1[10] = {0};
        memcpy(msg1, msg.data(), (size_t)size);
        char showString[50]={0};
        mycpy(showString,msg1,1);
        QString temp=showString;
        ui->textBrowser->append(temp);
    }
    else{
         QMessageBox::warning(this,"State Error","Please to connect!");
    }
}

void Widget::on_action2_clicked()
{
    if(socket->state()==QAbstractSocket::ConnectedState){
        socket->write("2");

        QByteArray msg = socket->readAll();
        int size = msg.size();
        char msg1[10] = {0};
        memcpy(msg1, msg.data(), (size_t)size);
        char showString[50]={0};
        mycpy(showString,msg1,2);
        QString temp=showString;
        ui->textBrowser->append(temp);
    }
    else{
         QMessageBox::warning(this,"State Error","Please to connect!");
    }
}

void Widget::on_action3_clicked()
{
    if(socket->state()==QAbstractSocket::ConnectedState){
        socket->write("3");

        QByteArray msg = socket->readAll();
        int size = msg.size();
        char msg1[10] = {0};
        memcpy(msg1, msg.data(), (size_t)size);
        char showString[50]={0};
        mycpy(showString,msg1,3);
        QString temp=showString;
        ui->textBrowser->append(temp);
    }
    else{
         QMessageBox::warning(this,"State Error","Please to connect!");

    }
}

void Widget::on_checkBox_clicked(bool checked)
{
    if(checked){
        socket->connectToHost("192.168.4.1",8080);
        socket->waitForConnected(3000);
        if(socket->state()!=QAbstractSocket::ConnectedState){
             ui->checkBox->setChecked(false);
            QMessageBox::warning(this,"Error","Connect Failure!");
            return;
        }
        //返回接受信息
        QByteArray msg = socket->readAll();
        int size = msg.size();
        char msg1[10] = {0};
        memcpy(msg1, msg.data(), (size_t)size);
        QString temp=msg1;
        ui->textBrowser->append(temp);
    }
    else{
        if(socket->state()==QAbstractSocket::ConnectedState)
        socket->disconnectFromHost();
    }
}


