#include "client.h"

Client::Client(const QString username, QObject *parent)
    : QObject{parent}
    , m_username(username)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    m_socket->connectToHost(host, port);
}

QTcpSocket *Client::getSocket() const
{
    return m_socket;
}

QString Client::getUsername() const
{
    return m_username;
}

void Client::onConnected()
{
    qDebug() << "Client::onConnected() " << m_username;
}

void Client::onDisconnected()
{
    qDebug() << "Client::onDisconnected() " << m_username;
}

void Client::onReadyRead()
{
    qDebug() << "Client::onReadyRead() " << m_username;
}
