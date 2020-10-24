#ifndef ADDADDRESSBOOKROW_H
#define ADDADDRESSBOOKROW_H

#include "tcpstructs.h"

#include <QWidget>

namespace Ui {
    class AddAddressBookRow;
}

namespace AddressBook{
namespace Client{

class AddAddressBookRowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddAddressBookRowWidget(QWidget *parent = 0);
    ~AddAddressBookRowWidget();

signals:
    void addRow(const AddressBookRow& AddressBookRow);

private:
    Ui::AddAddressBookRow *ui;

private slots:
    void pushButtonCancelClicked();
    void pushButtonAddClicked();
};

}
}

#endif // ADDADDRESSBOOKROW_H
