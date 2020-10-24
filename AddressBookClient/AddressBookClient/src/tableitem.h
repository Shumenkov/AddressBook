#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QVariant>

namespace AddressBook{
namespace Client{


class TableItem
{
public:
    explicit TableItem(const QVariant& data);

    QVariant data() const;
    void setData(const QVariant &data);

private:
    QVariant m_data;
};


}}

#endif // TABLEITEM_H
