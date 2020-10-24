#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>


namespace Ui {
class SettingsWidget;
}

namespace AddressBook{
namespace Client{

class Settings;

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

private:
    Ui::SettingsWidget *ui;
    Settings* m_settings;

    void saveSettings();
    void readSettings();

private slots:
    void pushButtonSaveClicked();
    void pushButtonCancelClicked();
    void pushButtonOKClicked();
};

}}

#endif // SETTINGSWIDGET_H
