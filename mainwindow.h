#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>//服务端只用socket

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
private slots:


    void connected_SLOT();
    void readyRead_Slot();


    void on_open_client_clicked();

    void on_close_client_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
