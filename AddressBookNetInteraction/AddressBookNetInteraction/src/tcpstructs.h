#ifndef TCPSTRUCTS_H
#define TCPSTRUCTS_H

#include <QtCore>

namespace AddressBook {

enum MessageType
{
    ADD_ADDR_BOOK_ROW = 0,
    SEND_ADDR_BOOK_DATA = 1,
    GET_ADDR_BOOK_DATA = 2,
    UPDATE_ADDR_BOOK_DATA = 3,
    ADD_ADDR_BOOK_ROW_FROM_SERVER = 4
};

struct AddressBookRow
{
    AddressBookRow(){}
    AddressBookRow(quint32 id_,
                   QString secondName_,
                   QString firstName_,
                   QString patronymic_,
                   QString gender_,
                   QString phoneNumber_):
        id(id_),
        secondName(secondName_),
        firstName(firstName_),
        patronymic(patronymic_),
        gender(gender_),
        phoneNumber(phoneNumber_)
    {}

    quint32 id;
    QString secondName;
    QString firstName;
    QString patronymic;
    QString gender;
    QString phoneNumber;
};
QDataStream &operator>> (QDataStream& s, AddressBookRow& p);
QDataStream &operator<< (QDataStream& s, const AddressBookRow& p);

struct AddressBookData
{
    AddressBookData(){}
    QList<AddressBookRow> list;
};
QDataStream &operator>> (QDataStream& s, AddressBookData& p);
QDataStream &operator<< (QDataStream& s, const AddressBookData& p);


}

#endif // TCPSTRUCTS_H
