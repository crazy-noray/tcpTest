#include "client.h"
#include <QtNetwork>

Client::Client()
{
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &Client::readMesaage);
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));;

    newConnection();
}

void Client::newConnection()
{
    blockSize = 0;
    m_tcpSocket->abort();
    m_tcpSocket->connectToHost("127.0.0.1", 6666);
}

void Client::readMesaage()
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    if (blockSize == 0) {
        if (m_tcpSocket->bytesAvailable() < static_cast<int>(sizeof(quint64))) {
            return;
        }
        in >> blockSize;
    }
    if (m_tcpSocket->bytesAvailable() < blockSize) {
        return;
    }
    in >> message;
    qDebug() << message;

}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << m_tcpSocket->errorString();
}
