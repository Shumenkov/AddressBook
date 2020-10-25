#ifndef TSPMESSAGES_H
#define TSPMESSAGES_H

#include "tcpstructs.h"

#include <QObject>

namespace AddressBook{
namespace Server{

class TcpServer;

//! \brief The TcpMessages class - формализованные сообщения для обмена данными с клиентом
class TcpMessages : public QObject
{
    Q_OBJECT
public:
    explicit TcpMessages(QObject *parent = nullptr);
    virtual ~TcpMessages();

    //! \brief sendAddressBookData - отправить клиенту данные в записной книге
    //! \param addressBookData - структура с данными о записной книге
    //! \param linkCount - номер соединения с клиентом
    void sendAddressBookData(const AddressBookData& addressBookData, const qint32 &linkCount);

    //! \brief addAddrBookRow - отправить клиенту сигнал что была добавленна новая запись в базу
    //! \param linkCount - номер соединения с клиентом
    //! \param addressBookRow - структура с записью
    void addAddrBookRow(const qint32 &linkCount, const AddressBookRow& addressBookRow);

    //! \brief sendRowRemoved - отправить клиенту сигнал что произошло удаление записий и БД
    //! \param linkCount - номер соединения с клиентом
    //! \param removedRowIDs - список id удаленных записей
    void sendRowRemoved(const qint32 &linkCount, const RemoveRowIDs &removedRowIDs);

signals:
    //! \brief getAddrBookData - испускается когда с сервера пришел запрос о выдаче данных о записной книге с сервера
    //! \param linkCount - номер соединения с клиентом
    void getAddrBookData(const qint32 &linkCount);

    //! \brief addAddrBookRowSignal - испускается когда клиент добавляет в базу новую запись
    //! \param linkCount - номер соединения с клиентом
    //! \param addressBookRow - структура с записью
    void addAddrBookRowSignal(const qint32 &linkCount, const AddressBookRow& addressBookRow);

    //! \brief removeRowSignal - испускается когда клиент удаляет записи
    //! \param linkCount - номер соединения с клиентом
    //! \param id - список id для удаления
    void removeRowSignal(const qint32 &linkCount, const RemoveRowIDs& id);

    //! \brief updateDataSignal - испускается когда клиент изменяет данные
    //! \param linkCount - номер соединения с клиентом
    //! \param addressBookData - структура с изменяемыми данными о записной книге
    void updateDataSignal(const qint32 &linkCount, const AddressBookData& addressBookData);

private:
    TcpServer* m_tcpServer;

    void parseAddAddrBookRow(const qint32 &linkCount, QDataStream &dataStream);
    void parseRemoveRow(const qint32 &linkCount, QDataStream &dataStream);
    void parseUpdateData(const qint32 &linkCount, QDataStream &dataStream);

private slots:
    void dataReceiveSlot(const qint32 &linkCount, const QByteArray &data);
};



}
}

#endif // TSPMESSAGES_H
