#ifndef TSPMESSAGES_H
#define TSPMESSAGES_H

#include "tcpstructs.h"

#include <QObject>

namespace AddressBook{
namespace Server{

class TcpServer;

class TcpMessages : public QObject
{
    Q_OBJECT
public:
    explicit TcpMessages(QObject *parent = nullptr);
    virtual ~TcpMessages();

    void sendAddressBookData(const AddressBookData& addressBookData, const qint32 &linkCount);
    void addAddrBookRow(const qint32 &linkCount, const AddressBookRow& addressBookRow);

signals:
    void getAddrBookData(const qint32 &linkCount);
    void addAddrBookRowSignal(const qint32 &linkCount, const AddressBookRow& addressBookRow);

public slots:

private:
    TcpServer* m_tcpServer;

    void parseAddAddrBookRow(const qint32 &linkCount, QDataStream &dataStream);

private slots:
    void dataReceiveSlot(const qint32 &linkCount, const QByteArray &data);
};



}
}

#endif // TSPMESSAGES_H