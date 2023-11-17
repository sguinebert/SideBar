#include "FiltersList.h"

FiltersList::FiltersList(QObject *parent) : QAbstractListModel(parent)
{

}

void FiltersList::addFilter(const QString &section, const QString &title, const QJsonObject &json)
{
    auto filter = new Filter(section, title, json, this);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_filters << filter;
    endInsertRows();
}

int FiltersList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_filters.count();
}

QVariant FiltersList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_filters.count())
        return QVariant();

    const Filter* filter = m_filters[index.row()];
    if (role == Section)
        return filter->section();
    else if (role == Title)
        return filter->title();
//    else if (role == datetime)
//        return study->datetime();
//    //else if (role == UuidRole)
//    //    return volume->uuid();
//    else if (role == series)
//        return study->series();
    return QVariant();
}

Filter *FiltersList::get(quint32 index) const
{
    if (index  >= m_filters.size())
        return nullptr;
    return m_filters[index];
}

bool FiltersList::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    while (count--) delete m_filters.takeAt(row);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> FiltersList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Section] = "section";
    roles[Title] = "title";
//    roles[UuidRole] = "uuid";
//    roles[StudyDescription] = "studyDescription";
//    roles[series] = "series";
    return roles;
}
