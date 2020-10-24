#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

namespace AddressBook{
namespace Client{


class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject* parent = nullptr);
    virtual ~TcpClient();

    void connectToHost(QHostAddress hostAddress, quint16 port);
    bool sendData(const QByteArray &data);
    void disconnectHost();

    bool isConnected() const;

signals:
    void connectedToHost();
    void disconnectedToHost();
    void resiveData(QByteArray);

public slots:
    void connectedSlot();
    void onReadyReadSlot();
    void disconnectSlot();

private:
    bool m_isConnected;
    QTcpSocket m_socket;
    bool isWaitReadData;
    quint32 m_sizePacketForRead;
    QTimer m_connectTimer;
    QHostAddress m_hostAddress;
    quint16 m_port;

private slots:
    void reconnectSlot();
};

}
}


