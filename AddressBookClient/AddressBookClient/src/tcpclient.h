#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

namespace AddressBook{
namespace Client{

//! \brief The TcpClient class - класс для соединения с сервером
class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject* parent = nullptr);
    virtual ~TcpClient();

    //! \brief connectToHost - присоединиться к серверу
    //! \param hostAddress - хост сервера
    //! \param port - порт сервера
    void connectToHost(QHostAddress hostAddress, quint16 port);

    //! \brief sendData - отправить данные на сервер
    //! \param data - данные
    //! \return - успешность отправки
    bool sendData(const QByteArray &data);

    //! \brief disconnectHost - отсоединиться от сервера
    void disconnectHost();

    bool isConnected() const;

signals:
    //! \brief connectedToHost - испускается когда произошло подключение к серверу
    void connectedToHost();

    //! \brief disconnectedToHost - испускается когда произошло отключение от серверу
    void disconnectedToHost();

    //! \brief resiveData - испускается когда с сервера пришли данные
    void resiveData(const QByteArray& data);

public slots:  
    //! \brief disconnectSlot - отключиться от сервера
    void disconnectSlot();

private:
    bool m_isConnected;
    QTcpSocket m_socket;
    bool isWaitReadData;
    quint32 m_sizePacketForRead;
    QTimer m_connectTimer;
    QHostAddress m_hostAddress;
    quint16 m_port;

private slots:
    void connectedSlot();
    void reconnectSlot();
    void onReadyReadSlot();
};

}
}


