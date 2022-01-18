#ifndef SERVER_H
#define SERVER_H
#include <QDialog>

class QTcpServer;
class Server : public QDialog
{
public:
    Server();

private:
    void sendMessage();
private:
    QTcpServer *m_tcpServer;
};

#endif // SERVER_H
