#include "addaddressbookrow.h"
#include "ui_addaddressbookrow.h"

namespace AddressBook{
namespace Client{

AddAddressBookRowWidget::AddAddressBookRowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAddressBookRow)
{
    ui->setupUi(this);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &AddAddressBookRowWidget::pushButtonAddClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &AddAddressBookRowWidget::pushButtonCancelClicked);
}

AddAddressBookRowWidget::~AddAddressBookRowWidget()
{
    delete ui;
}

void AddAddressBookRowWidget::pushButtonCancelClicked()
{
    this->close();
}

void AddAddressBookRowWidget::pushButtonAddClicked()
{
    AddressBookRow addressBookRow(0,
                                  ui->lineEditSName->text(),
                                  ui->lineEditFName->text(),
                                  ui->lineEditPatronymic->text(),
                                  ui->lineEditGender->text(),
                                  ui->lineEditPhoneNumber->text());
    emit addRow(addressBookRow);
    this->close();
}

}
}
