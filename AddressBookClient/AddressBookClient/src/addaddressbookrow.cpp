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

void AddAddressBookRowWidget::clearAll()
{
    ui->lineEditFName->clear();
    ui->lineEditSName->clear();
    ui->lineEditGender->clear();
    ui->lineEditPatronymic->clear();
    ui->lineEditPhoneNumber->clear();
}

void AddAddressBookRowWidget::pushButtonCancelClicked()
{
    clearAll();
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
    clearAll();
    this->close();
}

}
}
