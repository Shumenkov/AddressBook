#include "settingswidget.h"
#include "ui_settingswidget.h"

#include "settings.h"

namespace AddressBook{
namespace Client{


SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget),
    m_settings(Settings::getInstance())
{
    ui->setupUi(this);

    readSettings();

    connect(ui->pushButtonSave, &QPushButton::clicked, this, &SettingsWidget::pushButtonSaveClicked);
    connect(ui->pushButtonOK, &QPushButton::clicked, this, &SettingsWidget::pushButtonOKClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &SettingsWidget::pushButtonCancelClicked);
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::saveSettings()
{
    m_settings->setIpAddress(ui->lineEditServerIP->text());
    m_settings->setPort(ui->lineEditServerPort->text().toUInt());
}

void SettingsWidget::readSettings()
{
    ui->lineEditServerIP->setText(m_settings->ipAddress());
    ui->lineEditServerPort->setText(QString::number(m_settings->port()));
}

void SettingsWidget::pushButtonSaveClicked()
{
    saveSettings();
}

void SettingsWidget::pushButtonCancelClicked()
{
    this->close();
}

void SettingsWidget::pushButtonOKClicked()
{
    saveSettings();
    this->close();
}


}}
