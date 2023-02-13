#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>//服务端只用socket
#include <QtNetwork>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket *tcpsocket;

private:
    void get(QUrl u);

private slots:

    void finished();

    void sendcmd(QString cmd);

    void sendmsg(QString msg);

    void connected_SLOT();
    void readyRead_Slot();


    void on_open_client_clicked();

    void on_close_client_clicked();

    void on_send_clicked();

    void on_radioButton_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_SettingButton_clicked();

    void sendTest();

    void on_sendHttp_clicked();

private:
    Ui::MainWindow *ui;

    QUrl m_url;
    QString m_htmlText;
    QNetworkReply *m_pReply;
    QNetworkAccessManager m_manager;

};
#endif // MAINWINDOW_H
