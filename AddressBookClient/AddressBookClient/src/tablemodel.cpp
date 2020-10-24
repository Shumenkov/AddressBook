#include "tablemodel.h"
#include "tableitem.h"


namespace AddressBook{
namespace Client{


TableModel::TableModel(const quint16& columns, QObject *parent):
    QAbstractItemModel(parent),
    m_columns(columns)
{

}

TableModel::TableModel(const quint16& columns, QStringList header, QObject *parent):
    QAbstractItemModel(parent),
    m_columns(columns),
    m_header(header)
{

}

TableModel::~TableModel()
{
    for(int i = 0; i < m_lines.size(); ++i)
    {
        for(int j = 0; j < m_lines[i].size(); ++j)
        {
            delete m_lines[i][j];
        }
    }
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_lines.length();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columns;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!checkIndex(index))
        return QVariant();
    if(index.column()>=m_columns)
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_lines[index.row()][index.column()]->data();

    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (!checkIndex(index))
            return false;
        if(index.column()>=m_columns)
            return false;
        m_lines[index.row()][index.column()]->setData(value);
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

void TableModel::addRow(const QVector<TableItem* > &line)
{
    beginResetModel();
    m_lines.append(line);
    emit dataChanged(this->index(m_lines.size()-1, m_lines.size()-1),
                     this->index(m_lines.size()-1, m_lines.at(m_lines.size()-1).count()-1));
    endResetModel();
}

void TableModel::addRows(const QVector<QVector<TableItem *> > &lines)
{
    quint16 indexBeforeChanged = m_lines.size();
    beginResetModel();
    for(QVector<TableItem *> line : lines)
    {
        m_lines.append(line);
    }
    if(lines.size()>0)
    emit dataChanged(this->index(indexBeforeChanged, indexBeforeChanged),
                     this->index(m_lines.size()-1, m_lines.at(m_lines.size()-1).count()-1));
    endResetModel();
}

void TableModel::addEmptyRow()
{
    QVector<TableItem* > line;
    for(int i = 0; i < m_columns; ++i)
        line.append(new TableItem(QVariant()));

    beginResetModel();
    m_lines.append(line);
    emit dataChanged(this->index(m_lines.size()-1, m_lines.size()-1),
                     this->index(m_lines.size()-1, m_lines.at(m_lines.size()-1).count()-1));
    endResetModel();
}

void TableModel::removeRow(const int &row)
{
    if(row>=m_lines.size())
        return;

    beginResetModel();
    m_lines.removeAt(row);
    emit dataChanged(this->index(m_lines.size()-1, m_lines.size()-1),
                     this->index(m_lines.size()-1, m_lines.at(m_lines.size()-1).count()-1));
    endResetModel();
}

void TableModel::removeRow(const QModelIndexList &rows)
{
    beginResetModel();
    for(QModelIndex row : rows)
    {
        if(row.row()>=m_lines.size())
            continue;;
        m_lines.removeAt(row.row());
    }
    if(m_lines.size() > 0)
    emit dataChanged(this->index(m_lines.size()-1, m_lines.size()-1),
                     this->index(m_lines.size()-1, m_lines.at(m_lines.size()-1).count()-1));
    endResetModel();
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();
    if(row>=m_lines.size())
        return QModelIndex();
    if(column >= m_lines[row].size())
        return QModelIndex();

    TableItem *item = m_lines[row][column];
    if(column>=m_lines[row].size())
        return QModelIndex();

    return createIndex(row, column, item);
}

QModelIndex TableModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(section >= m_columns)
        return QVariant();

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return m_header[section];

    return QVariant();
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(m_header.size() < section)
        return false;

    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return false;

    m_header[section] = value.toString();
    emit headerDataChanged(orientation, section, section);

    return true;
}

}}
