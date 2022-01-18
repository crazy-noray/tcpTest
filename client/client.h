#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QAbstractSocket>
namespace Ui {
class MainWindow;
}

class QTcpSocket;
class Client : public QDialog
{
public:
    Client();

private:
    void newConnection();
    void readMesaage();
    void displayError(QAbstractSocket::SocketError);

private:
    QTcpSocket *m_tcpSocket = nullptr;
    QString message;
    quint64 blockSize;

};

#endif // CLIENT_H
