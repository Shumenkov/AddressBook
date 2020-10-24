#ifndef ADDRESSBOOKCLIENTWIDGET_H
#define ADDRESSBOOKCLIENTWIDGET_H

#include "tcpstructs.h"

#include <QWidget>
#include <QItemSelection>

QT_BEGIN_NAMESPACE
namespace Ui { class AddressBookClientWidget; }
QT_END_NAMESPACE

namespace AddressBook{
namespace Client{

class AddressBook;
class SettingsWidget;
class AddAddressBookRowWidget;

class AddressBookClientWidget : public QWidget
{
    Q_OBJECT

public:
    AddressBookClientWidget(QWidget *parent = nullptr);
    ~AddressBookClientWidget();

private:
    Ui::AddressBookClientWidget *ui;
    AddressBook* m_addressBook;
    SettingsWidget* m_settingsWidget;
    QModelIndexList m_selectedRows;
    bool isEditBook;
    AddAddressBookRowWidget* m_addAddressBookRowWidget;

    void setEditActive(bool isEdit);

private slots:
    void pushButtonSettingsClicked();
    void pushButtonAddLineClicked();
    void pushButtonRemoveLineClicked();
    void pushButtonEditClicked();
    void pushButtonCancelClicked();

    void tableViewDataChangedSlot(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void tableViewSelectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);
    void tableViewDoubleClickedSlot(const QModelIndex &index);

    void addAddressBookRowSlot(const AddressBookRow& addressBookRow);
};

}}

#endif // ADDRESSBOOKCLIENTWIDGET_H
