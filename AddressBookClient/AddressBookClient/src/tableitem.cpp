#include "tableitem.h"

namespace AddressBook{
namespace Client{

TableItem::TableItem(const QVariant& data) :
    m_data(data)
{

}

QVariant TableItem::data() const
{
    return m_data;
}

void TableItem::setData(const QVariant &data)
{
    m_data = data;
}

}}
