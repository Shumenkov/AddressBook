#include <QCoreApplication>
#include "addressbookserver.h"

using namespace AddressBook::Server;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AddressBookServer server;

    return a.exec();
}
