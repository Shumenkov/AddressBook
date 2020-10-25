#ifndef IMITATORSETTINGS_H
#define IMITATORSETTINGS_H

#include <QObject>
#include <QSettings>

namespace AddressBook{
namespace Server{


#define SETTINGS_NAME "settings.ini"

#define IP_ADDRESS "IP_ADDRESS"
#define DEFAULT_IP_ADDRESS "127.0.0.1"

#define PORT "PORT"
#define DEFAULT_PORT 50000

#define DB_NAME "DB_NAME"
#define DEFAULT_DB_NAME "address_book_base.sqlite"


class Settings;

class SettingsDestroyer
{
    Settings* _instanse;
public:
    ~SettingsDestroyer();
    void initialize(Settings* p);
};

//! \brief The Settings class - класс настроек приложения, настройки хранятся в ini файле
class Settings : public QObject
{
    Q_OBJECT

    static Settings* m_instance;
    static SettingsDestroyer destroyer;
    Settings();
    Settings& operator=(Settings&);
    ~Settings();
    friend class SettingsDestroyer;

public:
    static Settings* getInstance();

    QString ipAddress() const;
    void setIpAddress(const QString &ipAddress);

    quint32 port() const;
    void setPort(const quint32 &port);

    QString getDbName() const;
    void setDbName(const QString &dbName);

private:
    QSettings* settings;

    mutable QString m_ipAddress;
    mutable quint32 m_port;

    mutable QString m_dbName;
};


}
}

#endif // IMITATORSETTINGS_H
