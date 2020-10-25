#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include "tcpserverlink.h"

namespace AddressBook{
namespace Server{

//! \brief The TcpServer class - класс для работы с Tcp сервером
class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QString host = "", quint16 port = 0, QObject *parent = nullptr);
    virtual ~TcpServer();

    void close();
    void listen();

public slots:
    void sendData(const QByteArray &data, qint32 linkCount = -1);

signals:
    void dataPrepared(const qint32& linkCount, const QByteArray &data);
    void connected();

private:
    QTcpServer* m_server;
    QVector<TcpServerLink*> m_links;

private slots:
    void slotNewConnection();
    void linkDisconnected(const qint32& linkCount);
};


}}

#endif // TCPSERVER_H
