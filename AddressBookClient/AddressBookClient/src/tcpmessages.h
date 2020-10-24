#ifndef TCPMESSAGES_H
#define TCPMESSAGES_H

#include <QObject>
#include "tcpstructs.h"

namespace AddressBook{
namespace Client{

class TcpClient;

class TcpMessages : public QObject
{
    Q_OBJECT
public:
    explicit TcpMessages(QObject *parent = nullptr);
    virtual ~TcpMessages();

    void getAddressBookData();
    void addAddressBookRow(const AddressBookRow &addressBookRow);
    void updateAddressBookData(const AddressBookData& addressBookData);

signals:
    void setAddressBookData(const AddressBookData& addressBookData);
    void addAddrBookRow(const AddressBookRow& addressBookRow);
    void connectToServer();
    void disconnectToServer();

private:
    TcpClient* m_tcpClient;

    void parseAddrBookData(QDataStream &dataStream);
    void parseAddAddrBookRow(QDataStream &dataStream);

private slots:
    void dataReceiveSlot(const QByteArray &data);

};

}
}

#endif // TCPMESSAGES_H