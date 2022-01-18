#include "server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

Server::Server()
{
    m_tcpServer = new QTcpServer(this);

    if (!m_tcpServer->listen(QHostAddress::LocalHost, 6666)) {
        qDebug() << m_tcpServer->errorString();
        close();
    }
    connect(m_tcpServer, &QTcpServer::newConnection, this, &Server::sendMessage);
}

void Server::sendMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << static_cast<quint64>(0);
    out << tr("qqqqqqqqqqqqqqq");
    out.device()->seek(0);
    out << static_cast<quint64>(block.size() - sizeof(quint64));

    QTcpSocket *clientConnection = m_tcpServer->nextPendingConnection();
    connect(clientConnection, &QTcpSocket::disconnected, clientConnection, &QTcpSocket::deleteLater);

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
    qDebug() << "send success";
}

