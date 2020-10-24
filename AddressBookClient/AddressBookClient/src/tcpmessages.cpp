#include "tcpmessages.h"
#include "tcpclient.h"
#include "settings.h"

namespace AddressBook{
namespace Client{

TcpMessages::TcpMessages(QObject *parent) : QObject(parent),
    m_tcpClient(new TcpClient(this))
{
    Settings* settings = Settings::getInstance();
    m_tcpClient->connectToHost(QHostAddress(settings->ipAddress()), settings->port());

    connect(m_tcpClient, &TcpClient::connectedToHost, this, &TcpMessages::connectToServer);
    connect(m_tcpClient, &TcpClient::disconnectedToHost, this, &TcpMessages::disconnectToServer);
    connect(m_tcpClient, &TcpClient::resiveData, this, &TcpMessages::dataReceiveSlot);
}

TcpMessages::~TcpMessages()
{
    delete m_tcpClient;
}

void TcpMessages::getAddressBookData()
{
    QByteArray messageData;
    QDataStream messageDataStream(&messageData, QIODevice::ReadWrite);
    quint8 tcpMessageType = GET_ADDR_BOOK_DATA;
    messageDataStream<<tcpMessageType;
    m_tcpClient->sendData(messageData);
}

void TcpMessages::addAddressBookRow(const AddressBookRow &addressBookRow)
{
    QByteArray messageData;
    QDataStream messageDataStream(&messageData, QIODevice::ReadWrite);
    quint8 tcpMessageType = ADD_ADDR_BOOK_ROW;
    messageDataStream<<tcpMessageType;
    messageDataStream<<addressBookRow;
    m_tcpClient->sendData(messageData);
}

void TcpMessages::updateAddressBookData(const AddressBookData &addressBookData)
{
    QByteArray messageData;
    QDataStream messageDataStream(&messageData, QIODevice::ReadWrite);
    quint8 tcpMessageType = UPDATE_ADDR_BOOK_DATA;
    messageDataStream<<tcpMessageType;
    messageDataStream<<addressBookData;
    m_tcpClient->sendData(messageData);
}

void TcpMessages::parseAddrBookData(QDataStream &dataStream)
{
    AddressBookData addressBookData;
    dataStream>>addressBookData;
    emit setAddressBookData(addressBookData);
}

void TcpMessages::parseAddAddrBookRow(QDataStream &dataStream)
{
    AddressBookRow addressBookRow;
    dataStream>>addressBookRow;
    emit addAddrBookRow(addressBookRow);
}

void TcpMessages::dataReceiveSlot(const QByteArray &data)
{
    QDataStream inputStream(data);
    quint8 messageType;
    inputStream>>messageType;

    switch (messageType)
    {
    case SEND_ADDR_BOOK_DATA:
        parseAddrBookData(inputStream);
        break;
    case ADD_ADDR_BOOK_ROW_FROM_SERVER:
        parseAddAddrBookRow(inputStream);
        break;
    }
}

}
}
