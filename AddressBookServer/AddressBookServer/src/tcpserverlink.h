#ifndef TCPSERVERLINK_H
#define TCPSERVERLINK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


namespace AddressBook{
namespace Server{


class TcpServerLink : public QObject
{
    Q_OBJECT
public:
    explicit TcpServerLink(QTcpSocket* socket, quint32 linkCount, QObject *parent = nullptr);
    virtual ~TcpServerLink();

    bool sendData(const QByteArray &data);

    void close();
    void open();

signals:
    void dataReceive(qint32 linkCount, const QByteArray &data);
    void disconnected(qint32 linkCount);

private:
    qint32 m_linkCount;
    QTcpSocket* m_socket;
    bool m_isWaitReadData;
    quint32 m_sizePacketForRead;
    const quint8 m_dataSize = 4;
    bool m_isConnected;

private slots:
    void slotReadyRead();
    void slotDisconnected();
};


}}

#endif // TCPSERVERLINK_H
