#include "addressbook.h"
#include "tablemodel.h"
#include "tableitem.h"
#include "tcpmessages.h"
#include "enums.h"

namespace AddressBook{
namespace Client{


AddressBook::AddressBook(QObject *parent) : QObject(parent),
    m_tcpMessages(new TcpMessages(this))
{
    m_tableHeader << tr("id")
                  << tr("Second name")
                  << tr("First name")
                  << tr("Patronymic")
                  << tr("Gender")
                  << tr("Phone number");

    m_addressBookModel = new TableModel(addressBookColumnCount, m_tableHeader, this);

    connect(m_tcpMessages, &TcpMessages::connectToServer, this, &AddressBook::connectedToServerSlot);
    connect(m_tcpMessages, &TcpMessages::setAddressBookData, this, &AddressBook::setAddressBookDataSlot);
    connect(m_tcpMessages, &TcpMessages::addAddrBookRow, this, &AddressBook::addAddrBookRowSlot);
}

AddressBook::~AddressBook()
{
    if(m_addressBookModel!=nullptr)
        delete m_addressBookModel;
    delete m_tcpMessages;
}

QAbstractItemModel *AddressBook::addressBookModel()
{
    return m_addressBookModel;
}

void AddressBook::addLine(const AddressBookRow &addressBookRow)
{
    m_tcpMessages->addAddressBookRow(addressBookRow);
}

void AddressBook::removeLine(const int &row)
{
    m_addressBookModel->removeRow(row);
}

void AddressBook::removeLine(const QModelIndexList &rows)
{
    m_addressBookModel->removeRow(rows);
}

void AddressBook::addBufferChangeItem(const QModelIndex &index)
{
    if(!m_changedItemsBuffer.keys().contains(index))
        m_changedItemsBuffer.insert(index, m_addressBookModel->data(index));
}

void AddressBook::restoreModel()
{
    for(QModelIndex index : m_changedItemsBuffer.keys())
        m_addressBookModel->setData(index, m_changedItemsBuffer.value(index));

    m_changedItemsBuffer.clear();
}

void AddressBook::updateAddressBookRows(const QVector<quint16> &rows)
{
    AddressBookData addressBookData;
    AddressBookRow addressBookRow;
    QModelIndex index;
    for(quint16 row : rows)
    {
        index.sibling(row, AddressBookTableDataPosition::ID);
        addressBookRow.id = m_addressBookModel->data(index).toUInt();
        index.sibling(row, AddressBookTableDataPosition::SECOND_NAME);
        addressBookRow.secondName = m_addressBookModel->data(index).toString();
        index.sibling(row, AddressBookTableDataPosition::FIRST_NAME);
        addressBookRow.firstName = m_addressBookModel->data(index).toString();
        index.sibling(row, AddressBookTableDataPosition::PATRONYMIC);
        addressBookRow.patronymic = m_addressBookModel->data(index).toString();
        index.sibling(row, AddressBookTableDataPosition::GENDER);
        addressBookRow.gender = m_addressBookModel->data(index).toString();
        index.sibling(row, AddressBookTableDataPosition::PHONE_NUMBER);
        addressBookRow.phoneNumber = m_addressBookModel->data(index).toUInt();
        addressBookData.list.append(addressBookRow);
    }

    m_tcpMessages->updateAddressBookData(addressBookData);
}

QVector<TableItem *> AddressBook::fillTableModelRow(const AddressBookRow &addressBookRow)
{
    QVector<TableItem*> line;
    line.append(new TableItem(addressBookRow.id));
    line.append(new TableItem(addressBookRow.secondName));
    line.append(new TableItem(addressBookRow.firstName));
    line.append(new TableItem(addressBookRow.patronymic));
    line.append(new TableItem(addressBookRow.gender));
    line.append(new TableItem(addressBookRow.phoneNumber));
    return line;
}

void AddressBook::connectedToServerSlot()
{
    m_tcpMessages->getAddressBookData();
}

void AddressBook::setAddressBookDataSlot(const AddressBookData &addressBookData)
{
    QVector<QVector<TableItem*> > lines;
    for(AddressBookRow addressBookRow : addressBookData.list)
        lines.append(fillTableModelRow(addressBookRow));

    m_addressBookModel->addRows(lines);
}

void AddressBook::addAddrBookRowSlot(const AddressBookRow &addressBookRow)
{
    m_addressBookModel->addRow(fillTableModelRow(addressBookRow));
}

}}
