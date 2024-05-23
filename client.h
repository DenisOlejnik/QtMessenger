#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QString username, QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port);
    void sendMessage();

    QTcpSocket* getSocket() const { return m_socket; }
    QString getUsername() const { return m_username; }

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket *m_socket;
    QString m_username;
};

#endif // CLIENT_H
