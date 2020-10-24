#include "addressbookclientwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AddressBook::Client::AddressBookClientWidget addressBookClientWidget;
    addressBookClientWidget.show();

    return a.exec();
}
