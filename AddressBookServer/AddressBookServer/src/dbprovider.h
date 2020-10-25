#pragma once

#include "tcpstructs.h"

#include <QObject>
#include <QDateTime>
#include <QtSql>
#include <QFile>

namespace AddressBook{
namespace Server{

//! CREATE_FILE_NAME - название файла со скриптом создания базы данных
#define CREATE_FILE_NAME "db_create.sql"

//! \brief The DBProvider class - класс для работы с базой данных
class DBProvider : public QObject
{
    Q_OBJECT
public:
    explicit DBProvider(const QString& dbName, QObject *parent = 0);
    virtual ~DBProvider();

    //! \brief addAddressBookRow - добавить запись адресной книги в базу данных
    //! \param addressBookRow - структура с информацией о записи
    //! \return - id добавленной записи
    quint32 addAddressBookRow(const AddressBookRow& addressBookRow);

    //! \brief selectAddressBookData - выгрузить все записи адресной книги из базы данных
    //! \return - структура со списком записей адресной книги
    AddressBookData selectAddressBookData() const;

    //! \brief removeRow - удалить запись из базы данных
    //! \param id - id записи
    //! \return - успешность выполнения
    bool removeRow(const quint32& id);

    //! \brief updateAddressBookData - обновить данные в базе
    //! \param addressBookData - структура со списком записей адресной книги
    //! \return - успешность выполнения
    bool updateAddressBookData(const AddressBookData& addressBookData);

private:
    bool openDB();
    bool restoreDB();

    bool _isDBOpen;

    QString _dbName;
    QSqlDatabase _dataBase;
};

}}
