#include "tcpserverlink.h"
#include <QDataStream>

namespace AddressBook{
namespace Server{


TcpServerLink::TcpServerLink(QTcpSocket* socket, quint32 linkCount, QObject *parent) : QObject(parent),
    m_linkCount(linkCount),
    m_socket(socket),
    m_isWaitReadData(false),
    m_sizePacketForRead(0),
    m_isConnected(true)
{
    qDebug() << "Connected to client";
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpServerLink::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpServerLink::slotDisconnected);
}

TcpServerLink::~TcpServerLink()
{
    close();
}

bool TcpServerLink::sendData(const QByteArray &data)
{
    QByteArray size(m_dataSize, 0x0);
    QDataStream sizeStream(&size, QIODevice::WriteOnly);
    sizeStream<<quint32(data.size());

    if(m_socket->write(size)<0)
        return false;
    if(m_socket->write(data)<0)
        return false;
    return true;
}

void TcpServerLink::close()
{
    m_isConnected = false;
    m_socket->close();
}

void TcpServerLink::open()
{

}

void TcpServerLink::slotReadyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QDataStream inputStream(socket);
    while(true)
    {
        if(!m_isWaitReadData)
        {
            if(socket->bytesAvailable() >= 4)
            {
                inputStream >> m_sizePacketForRead;
                m_isWaitReadData = true;
            }
            else
                break;
        }

        if(m_isWaitReadData)
        {
            if(socket->bytesAvailable() >= m_sizePacketForRead)
            {
                QByteArray data(m_sizePacketForRead, 0x0);
                inputStream.readRawData(data.data(), data.size());
                emit dataReceive(m_linkCount, data);
                m_isWaitReadData = false;
            }
            else
                break;
        }
    }
}

void TcpServerLink::slotDisconnected()
{
    if(m_isConnected)
    {
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        socket->disconnectFromHost();
        emit disconnected(m_linkCount);
    }
}

}}
