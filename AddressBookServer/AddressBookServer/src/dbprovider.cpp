#include "dbprovider.h"

namespace AddressBook{
namespace Server{


DBProvider::DBProvider(const QString& dbName, QObject *parent)
    : QObject(parent)
    , _dbName(dbName)
    , _dataBase(QSqlDatabase::addDatabase("QSQLITE"))
{
    openDB();
}

DBProvider::~DBProvider()
{
    _dataBase.close();
    _dataBase.removeDatabase(QSqlDatabase::defaultConnection);
}

quint32 DBProvider::addAddressBookRow(const AddressBookRow &addressBookRow)
{
    QString queryHeadStr = "INSERT INTO address_book(second_name, first_name, patronymic, gender, phone_number) VALUES ('%1', '%2', '%3', '%4', '%5' );";
    QString queryStr = queryHeadStr.arg(addressBookRow.secondName).arg(addressBookRow.firstName)
            .arg(addressBookRow.patronymic).arg(addressBookRow.gender).arg(addressBookRow.phoneNumber);

    QSqlQuery query;
    if(!query.exec(queryStr))
        return 0;
    else
        return query.lastInsertId().toUInt();
}

AddressBookData DBProvider::selectAddressBookData() const
{
    AddressBookData addressBookData;
    AddressBookRow addressBookRow;

    QString queryHeadStr = "SELECT * FROM  address_book";
    QSqlQuery _query;

    if(!_query.exec(queryHeadStr))
        return addressBookData;
    QSqlRecord record = _query.record();

    while(_query.next())
    {
        addressBookRow.id = _query.value(record.indexOf("id")).toUInt();
        addressBookRow.secondName = _query.value(record.indexOf("second_name")).toString();
        addressBookRow.firstName = _query.value(record.indexOf("first_name")).toString();
        addressBookRow.patronymic = _query.value(record.indexOf("patronymic")).toString();
        addressBookRow.gender = _query.value(record.indexOf("gender")).toString();
        addressBookRow.phoneNumber = _query.value(record.indexOf("phone_number")).toString();
        addressBookData.list.append(addressBookRow);
    }

    return addressBookData;
}

bool DBProvider::removeRow(const quint32 &id)
{
    QString queryHeadStr = "DELETE FROM address_book WHERE id = %1;";
    QString queryStr = queryHeadStr.arg(QString::number(id));
    QSqlQuery query;
    if(query.exec(queryStr))
        return true;
    else
        return false;
}

bool DBProvider::updateAddressBookData(const AddressBookData &addressBookData)
{
    bool returnVal = true;
    for(AddressBookRow addressBookRow : addressBookData.list)
    {
        QString queryStr =  "UPDATE address_book SET second_name = '" + addressBookRow.secondName
                + "', first_name = '"+ addressBookRow.firstName
                +"', patronymic = '"+ addressBookRow.patronymic
                +"', gender = '"+ addressBookRow.gender
                +"', phone_number = '"+ addressBookRow.phoneNumber
                +"' WHERE id = " + QString::number(addressBookRow.id) + ";";
        QSqlQuery _query;
        if(!_query.exec(queryStr))
            returnVal = false;
    }

    return returnVal;
}

bool DBProvider::openDB()
{
    QFile dbFile(_dbName);
    if(dbFile.exists())
    {
        _dataBase.setDatabaseName(_dbName);
        if(!_dataBase.open())
        {
            qDebug()<<_dataBase.lastError();
            _isDBOpen = false;
        }
        else
            _isDBOpen = true;
    }
    else
        restoreDB();

    return _isDBOpen;
}

bool DBProvider::restoreDB()
{
    _dataBase.setDatabaseName(_dbName);
    if(!_dataBase.open())
    {
        qDebug()<<_dataBase.lastError();
        _isDBOpen = false;
        return false;
    }
    else
        _isDBOpen = true;

    QFile createFile(QDir::currentPath() + "/" + CREATE_FILE_NAME);
    if(!createFile.open(QIODevice::ReadOnly))
        return false;

    while(!createFile.atEnd())
    {
        QString queryStr = createFile.readLine();
        queryStr.remove("\n");
        QSqlQuery _query;
        if(!_query.exec(queryStr))
        {
            createFile.close();
            return false;
        }
    }
    createFile.close();
    return true;
}

}}

