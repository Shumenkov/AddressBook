#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QVector>
#include <QStringList>

namespace AddressBook{
namespace Client{

class TableItem;

//! \brief The TableModel class - кастомная модель таблицы
class TableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TableModel(const quint16& columns, QObject *parent = nullptr);
    explicit TableModel(const quint16& columns, QStringList header, QObject *parent = nullptr);
    virtual ~TableModel();

    QVariant headerData(int section, Qt::Orientation orientation, int role)const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    //! \brief addRow - добавить новую строку в модель
    //! \param line - строка
    void addRow(const QVector<TableItem *> &line);

    //! \brief addRows - добавть строки в модель
    //! \param lines - вектор строк
    void addRows(const QVector<QVector<TableItem *>> &lines);

    //! \brief addEmptyRow - добавить пустую строку в модель
    void addEmptyRow();

    //! \brief removeRow - удалить строку из модели
    //! \param row - номер строки
    void removeRow(const int& row);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    //! \brief indexByData - получить индекс ячейки таблицы по данным хранящимся в ней
    //! \param column - столбец в котором находится ячейка
    //! \param data - данные в ячейке
    //! \return - индекс
    QModelIndex indexByData(int column, const QVariant& data);

    QModelIndex parent(const QModelIndex &index) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //! \brief clearAll - удалить все данные из модели
    void clearAll();

private:
    quint16 m_columns;
    QVector<QVector<TableItem*> > m_lines;
    QStringList m_header;

signals:
    void editCompleted(const QString &);
};

}}

#endif // TABLEMODEL_H
