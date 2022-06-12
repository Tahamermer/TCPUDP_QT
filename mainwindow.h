

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextTable>
#include <QScrollBar>
#include <QSettings>
#include <QNetworkInterface>

#include "myudp.h"
#include "mytcpserver.h"
#include "mytcpclient.h"

#define TCPSERVER 10
#define TCPCLIENT 20
#define UDPSERVER 30
#define APPVERSION "V1.2"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  private slots:

    /******************************************************************************
     *
     * TCP Client
     *
     ******************************************************************************/
    void onTcpClientButtonClicked();
    void onTcpClientNewConnection(const QString &from, quint16 port);
    void onTcpClientStopButtonClicked();
    void onTcpClientTimeOut();
    void onTcpClientDisconnectButtonClicked();
    void onTcpClientDisconnected();
    void onTcpClientSendMessage();
    void onTcpClientAppendMessage(const QString &from, const QString &message);

    /******************************************************************************
     *
     * TCP Server
     *
     ******************************************************************************/
    void onTcpServerButtonClicked();
    void onTcpServerNewConnection(const QString &from, quint16 port);
    void onTcpServerStopButtonClicked();
    void onTcpServerDisconnectButtonClicked();
    void onTcpServerDisconnected();
    void onTcpServerSendMessage();
    void onTcpServerAppendMessage(const QString &from, const QString &message);

    /******************************************************************************
     *
     * UDP
     *
     ******************************************************************************/
    void onUdpButtonClicked();
    void onUdpStopButtonClicked();
    void onUdpSendMessage();
    void onUdpAppendMessage(const QString &from, const QString &message);

    void onRefreshButtonClicked();

    void on_tabWidget_currentChanged(int index);

    void on_comboBox_Interface_activated(int index);

    void on_button_TcpServer_clicked();

    void on_textBrowser_TcpClientMessage_textChanged();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  protected:
    void closeEvent(QCloseEvent *event);

  private:
    Ui::MainWindow *ui;
    void initUI();
    void loadSettings();
    void saveSettings();
    void findLocalIPs();
    bool setupConnection(quint8 type);

    void restoreWindowState();

    QTextTableFormat tableFormat;

    MyUDP *myudp = nullptr;
    MyTCPServer *mytcpserver = nullptr;
    MyTCPClient *mytcpclient = nullptr;

    QHostAddress tcpClientTargetAddr;
    quint16 tcpClientTargetPort;

    QHostAddress localAddr;

    quint16 tcpServerListenPort;

    quint16 udpListenPort;
    QHostAddress udpTargetAddr;
    quint16 udpTargetPort;

    QString settingsFileDir;
    QList<QNetworkInterface> interfaceList;
    quint8 type;

    QString messageUDP = "[UDP] ";
    QString messageTCP = "[TCP] ";
};

#endif // MAINWINDOW_H
