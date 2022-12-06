#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpsocket = new QTcpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::connected_SLOT()
{
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readyRead_Slot())); //将信号连接到槽，书写比较明确
}
void MainWindow::readyRead_Slot()//定义接收信号的槽
{
    QString buf;
    buf = tcpsocket->readAll();
    ui->receivewd->appendPlainText(buf);//接收由tcp发送过来的信息
}


void MainWindow::on_open_client_clicked()
{
    tcpsocket->connectToHost(ui->ipnum->text(), ui->portnum->text().toUInt()); //转为无符号，连接服务器端口
    connect(tcpsocket, SIGNAL(connected()), this, SLOT(connected_SLOT()));
    printf("打开客户端 ");
}

void MainWindow::on_close_client_clicked()
{
    tcpsocket->close();
    printf("关闭客户端 ");
}

void MainWindow::on_send_clicked()
{
    tcpsocket->write(ui->sendText->text().toLocal8Bit().data());
}
