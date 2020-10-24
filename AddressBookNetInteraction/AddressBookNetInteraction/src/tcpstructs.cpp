#include "tcpstructs.h"

namespace AddressBook {

QDataStream &operator>>(QDataStream &s, AddressBookRow &p)
{
    s >> p.id;
    s >> p.secondName;
    s >> p.firstName;
    s >> p.patronymic;
    s >> p.gender;
    s >> p.phoneNumber;
    return s;
}

QDataStream &operator<<(QDataStream &s, const AddressBookRow &p)
{
    s << p.id;
    s << p.secondName;
    s << p.firstName;
    s << p.patronymic;
    s << p.gender;
    s << p.phoneNumber;
    return s;
}

QDataStream &operator>>(QDataStream &s, AddressBookData &p)
{
    s >> p.list;
    return s;
}

QDataStream &operator<<(QDataStream &s, const AddressBookData &p)
{
    s << p.list;
    return s;
}

QDataStream &operator>>(QDataStream &s, RemoveRowIDs &p)
{
    s >> p.idList;
    return s;
}

QDataStream &operator<<(QDataStream &s, const RemoveRowIDs &p)
{
    s << p.idList;
    return s;
}



}
