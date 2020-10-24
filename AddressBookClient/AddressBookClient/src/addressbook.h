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

//! \brief The AddressBook class - класс реализующий основную логику приложения, хранит модель для отображения данных из БД
//! при вводе пользователем данных, изменения сначала отправляются на сервер, потом после записи изменений в БД
//! с сервера приходит ответ что данные изменены и только после этого модель обновляется
class AddressBook : public QObject
{
    Q_OBJECT
public:
    explicit AddressBook(QObject *parent = nullptr);
    virtual ~AddressBook();

    //! \brief addressBookModel - получить модель для отображения данных
    //! \return - модель для отображения данных
    QAbstractItemModel *addressBookModel();

    //! \brief addLine - добавть запись в адресную книгу
    //! \param addressBookRow - структура записи адресной книги
    void addLine(const AddressBookRow& addressBookRow);

    //! \brief removeLine - удалить запись из адресной книги
    //! \param row - номер строки
    void removeLine(const int& row);

    //! \brief removeLine - удалить запись из адресной книги
    //! \param rows - список индексов строк, подлежащих удалению
    void removeLine(const QModelIndexList& rows);


    //! \brief addBufferChangeItem - добавить в буфер данные модели до изменения
    //! \param index - индекс изменеяемой ячейки
    void addBufferChangeItem(const QModelIndex& index);

    //! \brief restoreModel - восстановить модель до изменений
    void restoreModel();

    //! \brief addChangedRow - добавить в буфер индексы измененных строк
    //! \param index - индекс измененной строки
    void addChangedRow(const QModelIndex& index);

    //! \brief saveChanged - сохранить изменения на сервере
    void saveChanged();

    //! \brief updateAddressBookRows - обновить строки в модели
    //! \param rows - номера строк
    void updateAddressBookRows(const QVector<quint16>& rows);

signals:

private:
    QStringList m_tableHeader;

    TableModel* m_addressBookModel;
    QMap<QModelIndex, QVariant> m_changedItemsBuffer;
    QList<QModelIndex> m_changedRows;

    TcpMessages* m_tcpMessages;

    QVector<TableItem *> fillTableModelRow(const AddressBookRow& addressBookRow);

private slots:
    //! \brief connectedToServerSlot - подключено к серверу
    void connectedToServerSlot();

    //! \brief disconnectedToServerSlot - отключено от сервера
    void disconnectedToServerSlot();

    //! \brief setAddressBookDataSlot - установить в модель данные пришедшие с сервера
    //! \param addressBookData - структура с данными об адресной книге
    void setAddressBookDataSlot(const AddressBookData& addressBookData);

    //! \brief addAddrBookRowSlot - добавть новую строку в модель пришедшую с сервера
    //! \param addressBookRow - структура с данными о строке в адресной книге
    void addAddrBookRowSlot(const AddressBookRow& addressBookRow);

    //! \brief rowRemovedSlot - удалить строки из медели пришедшие с сервера
    //! \param removedRowIDs - список удаленных id строк
    void rowRemovedSlot(const RemoveRowIDs& removedRowIDs);
};

}}

#endif // ADDRESSBOOK_H
