#ifndef ADDRESSBOOKSERVER_H
#define ADDRESSBOOKSERVER_H

#include <QObject>
#include "tcpstructs.h"

namespace AddressBook{
namespace Server{

    class TcpMessages;
    class DBProvider;
    class Settings;


class AddressBookServer : public QObject
{
    Q_OBJECT
public:
    explicit AddressBookServer(QObject *parent = nullptr);
    virtual ~AddressBookServer();

signals:

private:
    TcpMessages* m_tcpMessages;
    DBProvider* m_dbProvider;
    Settings* m_settings;

private slots:
    void addAddrBookRowSlot(const qint32 &linkCount, const AddressBookRow& addressBookRow);
    void getAddrBookDataSlot(const qint32 &linkCount);
};


}}

#endif // ADDRESSBOOKSERVER_H
