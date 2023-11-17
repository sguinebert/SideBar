#include "FilterListProxy.h"


FilterListProxy::FilterListProxy(QObject *parent) : QSortFilterProxyModel(parent)
{
    //    connect(this, &QSortFilterProxyModel::rowsInserted, this, &HeaderListProxy::countChanged);
    //    connect(this, &QSortFilterProxyModel::rowsRemoved, this, &HeaderListProxy::countChanged);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setDynamicSortFilter(true);

    //QSortFilterProxyModel::setSortRole(FilterList::Position);
    sort(0, Qt::AscendingOrder);
    //qDebug() << "sortcolumn : " << sortColumn() << " - " << sortRole() << " - " << columnCount();

}

int FilterListProxy::length() const
{
    auto source = sourceModel();
    return source->rowCount();
}

int FilterListProxy::roleKey(const QByteArray &role) const
{
    return roleNames().key(role, -1);
}

QHash<int, QByteArray> FilterListProxy::roleNames() const
{
    if (QAbstractItemModel *source = sourceModel())
        return source->roleNames();
    return QHash<int, QByteArray>();
}

bool FilterListProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    auto visible = true;// sourceModel()->data(sourceIndex, FilterList::Visibility);
    return qvariant_cast<bool>(visible);
}

