#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

bool Server::startServer(quint16 port)
{
    if (!m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "Server could not start!";
        return false;
    }
    return true;
}

void Server::sendMessage(const MessageInfo &message)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << message;
    for (QTcpSocket *client : m_clients) {
        client->write(data);
    }
    emit messageSent(message);
}

void Server::onNewConnection()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    m_clients.append(client);
    connect(client, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
    connect(client, &QTcpSocket::readyRead, this, &Server::onReadyRead);

    MessageInfo serviceMsg(true, "New client connected");
    emit serviceMessageRequested(serviceMsg);

    qDebug() << "New client connected!";
}

void Server::onClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    m_clients.removeAll(client);
    client->deleteLater();
    qDebug() << "Client disconnected!";
}

void Server::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    QDataStream in(clientSocket);
    MessageInfo message;
    in >> message;

    qDebug() << QString("Server received: %1 (%2)").arg(message.text()).arg(message.sender());

    for (QTcpSocket *client : m_clients) {
        if (client != clientSocket) {
            QByteArray data;
            QDataStream out(&data, QIODevice::WriteOnly);
            out << message;
            client->write(data);
        }
    }

    emit messageReceived(message);
}
