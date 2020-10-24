#include "tcpclient.h"
#include <QDataStream>

namespace AddressBook{
namespace Client{

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    m_isConnected = false;
    isWaitReadData = false;

    connect(&m_socket, SIGNAL(readyRead()), SLOT(onReadyReadSlot()));
    connect(&m_socket, SIGNAL(disconnected()), SLOT(disconnectSlot()));
    connect(&m_socket, SIGNAL(connected()), this, SLOT(connectedSlot()));

    connect(&m_connectTimer, SIGNAL(timeout()), this, SLOT(reconnectSlot()));
}

TcpClient::~TcpClient()
{
    m_socket.disconnectFromHost();
    m_socket.close();
}

void TcpClient::connectToHost(QHostAddress hostAddress, quint16 port)
{
    m_hostAddress = hostAddress;
    m_port = port;

    qDebug()<< Q_FUNC_INFO<<" try connect to " << m_hostAddress << " " << m_port;
    m_socket.connectToHost(m_hostAddress, m_port);

    m_connectTimer.setInterval(1000);
    m_connectTimer.setSingleShot(true);
    m_connectTimer.start();
}

bool TcpClient::sendData(const QByteArray &data)
{
    if(!m_isConnected)
        return false;

    QByteArray size(4, 0x00);
    if (quint64(data.size()) < 4294967295)
    {
        QDataStream sizeStream(&size, QIODevice::WriteOnly);
        sizeStream<<quint32(data.size());
    }

    if (m_socket.write(size) < 0)
        return false;

    if (m_socket.write(data) < 0)
        return false;

    return true;
}

void TcpClient::disconnectHost()
{
    m_connectTimer.stop();
    m_socket.disconnectFromHost();
    m_isConnected = false;
}

void TcpClient::connectedSlot()
{
    qDebug()<< Q_FUNC_INFO<<" connected to " << m_hostAddress << " " << m_port;
    m_isConnected = true;
    emit connectedToHost();
    m_connectTimer.stop();
}

void TcpClient::onReadyReadSlot()
{
    QDataStream inputStream(&m_socket);
    while (true)
    {
        if (!isWaitReadData)
        {
            if (m_socket.bytesAvailable() >= 4)
            {
                inputStream >> m_sizePacketForRead;
                isWaitReadData = true;
            } else break;
        }

        if (isWaitReadData) {
            if (m_socket.bytesAvailable()  >= m_sizePacketForRead)
            {
                QByteArray data(m_sizePacketForRead, 0x00);
                inputStream.readRawData(data.data(), data.size());
                emit resiveData(data);

                isWaitReadData = false;
            } else break;
        }
    }
}

void TcpClient::disconnectSlot()
{
    m_socket.disconnectFromHost();
    m_isConnected = false;
    emit disconnectedToHost();
    reconnectSlot();
}

bool TcpClient::isConnected() const
{
    return m_isConnected;
}

void TcpClient::reconnectSlot()
{
    qDebug()<< Q_FUNC_INFO<<" try connect to " << m_hostAddress << " " << m_port;
    m_socket.connectToHost(m_hostAddress, m_port);
    m_connectTimer.start();
}

}
}
