#include "settings.h"

#include <QDir>

namespace AddressBook{
namespace Server{

Settings* Settings::m_instance = 0;
SettingsDestroyer Settings::destroyer;
SettingsDestroyer::~SettingsDestroyer() { delete _instanse; }
void SettingsDestroyer::initialize(Settings *p) { _instanse = p; }

Settings *Settings::getInstance()
{
    if(!m_instance)
    {
        m_instance = new Settings();
        destroyer.initialize(m_instance);
    }
    return m_instance;
}

Settings::Settings()
{
    QString settingsPath = QDir::currentPath() + "/" + SETTINGS_NAME;
    settings = new QSettings(settingsPath, QSettings::IniFormat);
}

Settings::~Settings()
{
    delete settings;
}

QString Settings::ipAddress() const
{
    m_ipAddress = settings->value(IP_ADDRESS).toString();
    if(m_ipAddress.isEmpty())
    {
        m_ipAddress = DEFAULT_IP_ADDRESS;
        settings->setValue(IP_ADDRESS, m_ipAddress);
    }
    return m_ipAddress;
}

void Settings::setIpAddress(const QString &ipAddress)
{
    m_ipAddress = ipAddress;
    settings->setValue(IP_ADDRESS, m_ipAddress);
}

quint32 Settings::port() const
{
    m_port = settings->value(PORT).toUInt();
    if(m_port == 0)
    {
        m_port = DEFAULT_PORT;
        settings->setValue(PORT, m_port);
    }
    return m_port;
}

void Settings::setPort(const quint32 &port)
{
    m_port = port;
    settings->setValue(PORT, m_port);
}

QString Settings::getDbName() const
{
    m_dbName = settings->value(DB_NAME).toString();
    if(m_dbName.isEmpty())
    {
        m_dbName = DEFAULT_DB_NAME;
        settings->setValue(DB_NAME, m_dbName);
    }
    return m_dbName;
}

void Settings::setDbName(const QString &dbName)
{
    m_dbName = dbName;
    settings->setValue(DB_NAME, m_dbName);
}

}
}
