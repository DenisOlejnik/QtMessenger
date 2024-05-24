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

void Client::sendMessage(const QString &text)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qWarning() << QString("[warn] [Client::sendMessage] %1 has non 'Connected' state.").arg(m_username);
        return;
    }

    MessageInfo message(getUsername(), text);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << message;

    m_socket->write(block);
    qDebug() << QString("(%1) sent message: %2").arg(m_username).arg(message.text());
    emit messageSent(message);
}

void Client::onConnected()
{
    qDebug() << "Client connected: " << m_username;
}

void Client::onDisconnected()
{
    qDebug() << "Client disconnected: " << m_username;
}

void Client::onReadyRead()
{
    qDebug() << QString("(%1) got new message: ").arg(m_username);
    QDataStream in(m_socket);
    MessageInfo message;
    in >> message;

    emit messageReceived(message);
}
