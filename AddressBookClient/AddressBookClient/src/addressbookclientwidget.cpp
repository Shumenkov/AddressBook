#include "addressbookclientwidget.h"
#include "ui_addressbookclientwidget.h"

#include "addressbook.h"
#include "settingswidget.h"
#include "addaddressbookrow.h"
#include "enums.h"

namespace AddressBook {
namespace Client {

AddressBookClientWidget::AddressBookClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddressBookClientWidget)
    , m_settingsWidget(new SettingsWidget)
    , isEditBook(false)
    , m_addAddressBookRowWidget(new AddAddressBookRowWidget)
{
    ui->setupUi(this);

    setEditActive(false);

    m_addressBook = new AddressBook();
    ui->tableViewAddressBook->setModel(m_addressBook->addressBookModel());
    ui->tableViewAddressBook->setColumnHidden(AddressBookTableDataPosition::ID, true);
    ui->tableViewAddressBook->horizontalHeader()->setSectionResizeMode(AddressBookTableDataPosition::SECOND_NAME, QHeaderView::Stretch);
    ui->tableViewAddressBook->horizontalHeader()->setSectionResizeMode(AddressBookTableDataPosition::FIRST_NAME, QHeaderView::Stretch);
    ui->tableViewAddressBook->horizontalHeader()->setSectionResizeMode(AddressBookTableDataPosition::PATRONYMIC, QHeaderView::Stretch);

    connect(ui->tableViewAddressBook, &QTableView::doubleClicked, this, &AddressBookClientWidget::tableViewDoubleClickedSlot);
    connect(ui->tableViewAddressBook->model(), &QAbstractItemModel::dataChanged,
            this, &AddressBookClientWidget::tableViewDataChangedSlot);
    connect(ui->tableViewAddressBook->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &AddressBookClientWidget::tableViewSelectionChangedSlot);

    connect(ui->pushButtonSettings, &QPushButton::clicked, this, &AddressBookClientWidget::pushButtonSettingsClicked);
    connect(ui->pushButtonAddLine, &QPushButton::clicked, this, &AddressBookClientWidget::pushButtonAddLineClicked);
    connect(ui->pushButtonRemoveLine, &QPushButton::clicked, this, &AddressBookClientWidget::pushButtonRemoveLineClicked);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &AddressBookClientWidget::pushButtonEditClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &AddressBookClientWidget::pushButtonCancelClicked);
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &AddressBookClientWidget::pushButtonSaveClicked);

    connect(m_addAddressBookRowWidget, &AddAddressBookRowWidget::addRow, this, &AddressBookClientWidget::addAddressBookRowSlot);
}

AddressBookClientWidget::~AddressBookClientWidget()
{
    delete ui;
    delete m_settingsWidget;
    delete m_addAddressBookRowWidget;
    delete m_addressBook;
}

void AddressBookClientWidget::setEditActive(bool isEdit)
{
    ui->pushButtonAddLine->setEnabled(!isEdit);
    ui->pushButtonRemoveLine->setEnabled(!isEdit);
    ui->pushButtonCancel->setVisible(isEdit);
    ui->pushButtonSave->setVisible(isEdit);
    ui->pushButtonEdit->setEnabled(!isEdit);
    if(isEdit)
        ui->tableViewAddressBook->setEditTriggers(QAbstractItemView::DoubleClicked);
    else
        ui->tableViewAddressBook->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AddressBookClientWidget::pushButtonSettingsClicked()
{
    m_settingsWidget->show();
    m_settingsWidget->setFocus();
}

void AddressBookClientWidget::pushButtonAddLineClicked()
{
    m_addAddressBookRowWidget->show();
}

void AddressBookClientWidget::pushButtonRemoveLineClicked()
{
    m_addressBook->removeLine(m_selectedRows);
}

void AddressBookClientWidget::pushButtonEditClicked()
{
    if(isEditBook)
    {
        isEditBook = false;
        setEditActive(isEditBook);
    }
    else
    {
        isEditBook = true;
        setEditActive(isEditBook);
    }
}

void AddressBookClientWidget::pushButtonCancelClicked()
{
    m_addressBook->restoreModel();
    isEditBook = false;
    setEditActive(isEditBook);
}

void AddressBookClientWidget::pushButtonSaveClicked()
{
    m_addressBook->saveChanged();
    isEditBook = false;
    setEditActive(isEditBook);
}

void AddressBookClientWidget::tableViewDataChangedSlot(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(bottomRight);
    Q_UNUSED(roles);

    if(isEditBook)
        m_addressBook->addChangedRow(topLeft);
}

void AddressBookClientWidget::tableViewSelectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    m_selectedRows = ui->tableViewAddressBook->selectionModel()->selectedRows();
}

void AddressBookClientWidget::tableViewDoubleClickedSlot(const QModelIndex &index)
{
    m_addressBook->addBufferChangeItem(index);
}

void AddressBookClientWidget::addAddressBookRowSlot(const AddressBookRow &addressBookRow)
{
    m_addressBook->addLine(addressBookRow);
}

}}



