#include "addressbookclientwidget.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtLanguageTranslator;
    qtLanguageTranslator.load(QString("translation_") + QString("ru_RU"));
    qApp->installTranslator(&qtLanguageTranslator);

    AddressBook::Client::AddressBookClientWidget addressBookClientWidget;
    addressBookClientWidget.show();

    return a.exec();
}
