QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include($$PWD/src/src.pri)

INCLUDEPATH += ../../AddressBookNetInteraction/AddressBookNetInteraction/src
LIBS += -L../../AddressBookNetInteraction/AddressBookNetInteraction/debug -lAddressBookNetInteraction
LIBS += -L../../AddressBookNetInteraction/AddressBookNetInteraction/release -lAddressBookNetInteraction

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
