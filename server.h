#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QObject>

#include <messageinfo.h>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    bool startServer(quint16 port);
    void sendMessage(const MessageInfo &message);

signals:
    void messageReceived(const MessageInfo &message);
    void messageSent(const MessageInfo &message);
    void serviceMessageRequested(const MessageInfo &message);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    QTcpServer *m_server;
    QList <QTcpSocket*> m_clients;
};

#endif // SERVER_H
