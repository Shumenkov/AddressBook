#include "addressbookserver.h"
#include "tspmessages.h"
#include "dbprovider.h"
#include "settings.h"

namespace AddressBook{
namespace Server{


AddressBookServer::AddressBookServer(QObject *parent) : QObject(parent),
    m_tcpMessages(new TcpMessages(this)),
    m_settings(Settings::getInstance())
{
    QString dbPath = QDir::currentPath() + "/" + m_settings->getDbName();
    m_dbProvider = new DBProvider(dbPath,this);
    connect(m_tcpMessages, &TcpMessages::addAddrBookRowSignal, this, &AddressBookServer::addAddrBookRowSlot);
    connect(m_tcpMessages, &TcpMessages::getAddrBookData, this, &AddressBookServer::getAddrBookDataSlot);

}

AddressBookServer::~AddressBookServer()
{
    delete m_tcpMessages;
    delete m_dbProvider;
}

void AddressBookServer::addAddrBookRowSlot(const qint32 &linkCount, const AddressBookRow &addressBookRow)
{
    quint32 addRowId = m_dbProvider->addAddressBookRow(addressBookRow);
    if(addRowId>0)
    {
        AddressBookRow addedAddressBookRow = addressBookRow;
        addedAddressBookRow.id = addRowId;
        m_tcpMessages->addAddrBookRow(linkCount, addedAddressBookRow);
    }
}

void AddressBookServer::getAddrBookDataSlot(const qint32 &linkCount)
{
    AddressBookData addressBookData = m_dbProvider->selectAddressBookData();
    m_tcpMessages->sendAddressBookData(addressBookData, linkCount);
}


}}
