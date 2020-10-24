#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QVector>
#include <QStringList>

namespace AddressBook{
namespace Client{

class TableItem;

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

    void addRow(const QVector<TableItem *> &line);
    void addRows(const QVector<QVector<TableItem *>> &lines);
    void addEmptyRow();

    void removeRow(const int& row);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex indexByData(int column, const QVariant& data);
    QModelIndex parent(const QModelIndex &index) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    quint16 m_columns;
    QVector<QVector<TableItem*> > m_lines;
    QStringList m_header;

signals:
    void editCompleted(const QString &);
};

}}

#endif // TABLEMODEL_H
