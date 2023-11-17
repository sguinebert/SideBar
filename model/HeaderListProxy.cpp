#include "HeaderListProxy.h"

#include "HeaderList.h"

HeaderListProxy::HeaderListProxy(QObject *parent) : QSortFilterProxyModel(parent)
{
//    connect(this, &QSortFilterProxyModel::rowsInserted, this, &HeaderListProxy::countChanged);
//    connect(this, &QSortFilterProxyModel::rowsRemoved, this, &HeaderListProxy::countChanged);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setDynamicSortFilter(true);

    QSortFilterProxyModel::setSortRole(HeaderList::Position);
    sort(0, Qt::AscendingOrder);
    //qDebug() << "sortcolumn : " << sortColumn() << " - " << sortRole() << " - " << columnCount();

}

int HeaderListProxy::length() const
{
    auto source = (HeaderList*) sourceModel();
    return source->length();
}

int HeaderListProxy::roleKey(const QByteArray &role) const
{
    return roleNames().key(role, -1);
}

QHash<int, QByteArray> HeaderListProxy::roleNames() const
{
    if (QAbstractItemModel *source = sourceModel())
        return source->roleNames();
    return QHash<int, QByteArray>();
}

bool HeaderListProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    auto visible = sourceModel()->data(sourceIndex, HeaderList::Visibility);
    return qvariant_cast<bool>(visible);
}

