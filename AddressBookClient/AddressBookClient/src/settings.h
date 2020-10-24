#ifndef IMITATORSETTINGS_H
#define IMITATORSETTINGS_H

#include <QObject>
#include <QSettings>

namespace AddressBook{
namespace Client{

#define SETTINGS_NAME "AirConditiongController.ini"

#define IP_ADDRESS "IP_ADDRESS"
#define DEFAULT_IP_ADDRESS "127.0.0.1"

#define PORT "PORT"
#define DEFAULT_PORT 50000

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

    QString ipAddress();
    void setIpAddress(const QString &ipAddress);

    quint32 port();
    void setPort(const quint32 &port);

private:
    QSettings* settings;

    QString m_ipAddress;
    quint32 m_port;
};


}
}

#endif // IMITATORSETTINGS_H
