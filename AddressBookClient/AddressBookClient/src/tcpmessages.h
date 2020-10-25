#ifndef TCPMESSAGES_H
#define TCPMESSAGES_H

#include <QObject>
#include "tcpstructs.h"

namespace AddressBook{
namespace Client{

class TcpClient;

//! \brief The TcpMessages class - формализованные сообщения для обмена данными с сервером
class TcpMessages : public QObject
{
    Q_OBJECT
public:
    explicit TcpMessages(QObject *parent = nullptr);
    virtual ~TcpMessages();

    //! \brief getAddressBookData - запрос данных с сервера
    void getAddressBookData();

    //! \brief addAddressBookRow - добавить новую строку на сервер
    //! \param addressBookRow - структура с записью в записной книге
    void addAddressBookRow(const AddressBookRow &addressBookRow);

    //! \brief updateAddressBookData - обновить данные на сервере
    //! \param addressBookData - структура с данными о записной книге
    void updateAddressBookData(const AddressBookData& addressBookData);

    //! \brief removeRow - удалить строки с сервера
    //! \param removeRowIDs - список удаляемых id
    void removeRow(const RemoveRowIDs &removeRowIDs);

signals:
    //! \brief setAddressBookData - испускается когда с сервера пришли данные о записной книге
    //! \param addressBookData
    void setAddressBookData(const AddressBookData& addressBookData);

    //! \brief addAddrBookRow - испускается когда на сервере была добавлена строка
    //! \param addressBookRow
    void addAddrBookRow(const AddressBookRow& addressBookRow);

    //! \brief rowRemovedSignal - испускается когда на сервере была удалена строка
    //! \param id
    void rowRemovedSignal(const RemoveRowIDs& id);

    //! \brief connectToServer - испускается когда произошло подключение к серверу
    void connectToServer();

    //! \brief disconnectToServer - испускается когда произошло отключение от серверу
    void disconnectToServer();

private:
    TcpClient* m_tcpClient;

    void parseAddrBookData(QDataStream &dataStream);
    void parseAddAddrBookRow(QDataStream &dataStream);
    void parseRowRemoved(QDataStream &dataStream);

private slots:
    void dataReceiveSlot(const QByteArray &data);

};

}
}

#endif // TCPMESSAGES_H
