#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "tcpstructs.h"

#include <QObject>
#include <QAbstractTableModel>

namespace AddressBook{
namespace Client{

class TableModel;
class TableItem;
class TcpMessages;

const quint16 addressBookColumnCount = 6;

class AddressBook : public QObject
{
    Q_OBJECT
public:
    explicit AddressBook(QObject *parent = nullptr);
    virtual ~AddressBook();

    QAbstractItemModel *addressBookModel();
    void addLine(const AddressBookRow& addressBookRow);
    void removeLine(const int& row);
    void removeLine(const QModelIndexList& rows);

    void addBufferChangeItem(const QModelIndex& index);
    void restoreModel();

    void updateAddressBookRows(const QVector<quint16>& rows);

signals:

private:
    QStringList m_tableHeader;

    TableModel* m_addressBookModel;
    QMap<QModelIndex, QVariant> m_changedItemsBuffer;

    TcpMessages* m_tcpMessages;

    QVector<TableItem *> fillTableModelRow(const AddressBookRow& addressBookRow);

private slots:
    void connectedToServerSlot();
    void setAddressBookDataSlot(const AddressBookData& addressBookData);
    void addAddrBookRowSlot(const AddressBookRow& addressBookRow);
};

}}

#endif // ADDRESSBOOK_H
