#pragma once

#include "tcpstructs.h"

#include <QObject>
#include <QDateTime>
#include <QtSql>
#include <QFile>

namespace AddressBook{
namespace Server{

#define CREATE_FILE_NAME "db_create.sql"
class DBProvider : public QObject
{
    Q_OBJECT
public:
    explicit DBProvider(QString dbName, QObject *parent = 0);
    virtual ~DBProvider();

    quint32 addAddressBookRow(const AddressBookRow& addressBookRow);

    AddressBookData selectAddressBookData() const;

signals:

public slots:

private:
    bool openDB();
    bool restoreDB();

    bool _isDBOpen;

    QString _dbName;
    QSqlDatabase _dataBase;
};

}}
