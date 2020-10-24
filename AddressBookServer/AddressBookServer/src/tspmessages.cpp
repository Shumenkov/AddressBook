#include "tspmessages.h"
#include "tcpserver.h"


namespace AddressBook{
namespace Server{

TcpMessages::TcpMessages(QObject *parent) : QObject(parent),
    m_tcpServer(new TcpServer)
{
    connect(m_tcpServer, &TcpServer::dataPrepared, this, &TcpMessages::dataReceiveSlot);
}

TcpMessages::~TcpMessages()
{
    delete m_tcpServer;
}

void TcpMessages::sendAddressBookData(const AddressBookData &addressBookData, const qint32 &linkCount)
{
    QByteArray messageData;
    QDataStream messageDataStream(&messageData, QIODevice::ReadWrite);
    quint8 tcpMessageType = SEND_ADDR_BOOK_DATA;
    messageDataStream<<tcpMessageType;
    messageDataStream<<addressBookData;
    m_tcpServer->sendData(messageData, linkCount);
}

void TcpMessages::addAddrBookRow(const qint32 &linkCount, const AddressBookRow &addressBookRow)
{
    QByteArray messageData;
    QDataStream messageDataStream(&messageData, QIODevice::ReadWrite);
    quint8 tcpMessageType = ADD_ADDR_BOOK_ROW_FROM_SERVER;
    messageDataStream<<tcpMessageType;
    messageDataStream<<addressBookRow;
    m_tcpServer->sendData(messageData, linkCount);
}

void TcpMessages::parseAddAddrBookRow(const qint32 &linkCount, QDataStream &dataStream)
{
    AddressBookRow addressBookRow;
    dataStream>>addressBookRow;
    emit addAddrBookRowSignal(linkCount, addressBookRow);
}

void TcpMessages::dataReceiveSlot(const qint32 &linkCount, const QByteArray &data)
{
    QDataStream inputStream(data);
    quint8 messageType;
    inputStream>>messageType;

    switch (messageType)
    {
    case GET_ADDR_BOOK_DATA:
        emit getAddrBookData(linkCount);
        break;
    case ADD_ADDR_BOOK_ROW:
        parseAddAddrBookRow(linkCount, inputStream);
        break;
    }
}

}
}
