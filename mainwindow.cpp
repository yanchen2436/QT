#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SQLite.h"

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
void MainWindow::sendcmd(QString cmd)
{
    cmd = "_cmd_" + cmd + "_cmd_";
    tcpsocket->write(cmd.toLocal8Bit().data());
}
void MainWindow::sendmsg(QString msg)
{
    msg = "_msg_" + msg + "_msg_";
    tcpsocket->write(msg.toLocal8Bit().data());
};
void MainWindow::connected_SLOT()
{
    connect(tcpsocket, SIGNAL(readyRead()), this, SLOT(readyRead_Slot())); //将信号连接到槽，书写比较明确
}
void MainWindow::readyRead_Slot()   //定义接收信号的槽
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
void MainWindow::on_send_clicked()   //发送按钮
{
    MainWindow::sendmsg(ui->sendText->text());
}
void MainWindow::on_radioButton_clicked()
{
    MainWindow::sendcmd("show");
}
void MainWindow::on_radioButton_5_clicked()
{
    MainWindow::sendcmd("upsideDown");
}
void MainWindow::on_radioButton_3_clicked()
{
    MainWindow::sendcmd("flipSide");
}
void MainWindow::on_radioButton_2_clicked()
{
    MainWindow::sendcmd("diagonalFlip");
}
void MainWindow::on_SettingButton_clicked()
{
    QString expmode = "expmode:";
    expmode = expmode + ui->expmode->currentIndex();
    MainWindow::sendcmd(expmode);
    QString metime = "metime:";
    metime = metime + ui->metime->text();
    MainWindow::sendcmd(metime);
    QString meagain = "meagain:";
    meagain = meagain + ui->meagain->text();
    MainWindow::sendcmd(meagain);
    QString medgain = "medgain:";
    medgain = medgain + ui->medgain->text();
    MainWindow::sendcmd(medgain);
}

void MainWindow::on_pushButton_clicked()
{
    SQLController sql;
    sql.SQLconnection();
}

void MainWindow::get(QUrl u)
{
    m_url = u;
    if (m_pReply != Q_NULLPTR) {
        // 更改reply指向位置前一定要保证之前的定义了自动delete
        m_pReply->deleteLater();
    }
    QNetworkRequest request;
    request.setUrl(m_url);
    m_pReply = m_manager.get(request);
    qDebug() << "start get";
    connect(m_pReply, &QNetworkReply::finished, this, &MainWindow::finished);
}

void MainWindow::finished()
{
    QByteArray bytes = m_pReply->readAll();
    m_pReply->deleteLater();
    m_pReply = Q_NULLPTR;
    const QVariant redirectionTarget = m_pReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!redirectionTarget.isNull()) {
        //如果网址跳转重新请求
        const QUrl redirectedUrl = m_url.resolved(redirectionTarget.toUrl());
        qDebug() << "redirectedUrl:" << redirectedUrl.url();
        get(redirectedUrl);
        return;
    }
    qDebug() << "finished";
    m_htmlText = bytes;
    qDebug() << "get ready,read size:" << m_htmlText.size();
    // 写入文件
    QFile f("result.html");
    f.open(QFile::WriteOnly);
    f.write(bytes);
}

void MainWindow::on_sendHttp_clicked()
{
}


