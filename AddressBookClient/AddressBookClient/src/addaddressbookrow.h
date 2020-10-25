#ifndef ADDADDRESSBOOKROW_H
#define ADDADDRESSBOOKROW_H

#include "tcpstructs.h"

#include <QWidget>

namespace Ui {
    class AddAddressBookRow;
}

namespace AddressBook{
namespace Client{

//! \brief The AddAddressBookRowWidget class - класс для отображения окна добавления новой записи
class AddAddressBookRowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddAddressBookRowWidget(QWidget *parent = 0);
    ~AddAddressBookRowWidget();

signals:
    //! \brief addRow - Была добавленна новая запись
    //! \param AddressBookRow - структура с данными о новой записи
    void addRow(const AddressBookRow& AddressBookRow);

private:
    Ui::AddAddressBookRow *ui;

    void clearAll();

private slots:
    void pushButtonCancelClicked();
    void pushButtonAddClicked();
};

}
}

#endif // ADDADDRESSBOOKROW_H
