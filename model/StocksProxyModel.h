#ifndef STOCKSPROXYMODEL_H
#define STOCKSPROXYMODEL_H
#include <QSortFilterProxyModel>
#include <QObject>

class StocksProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    StocksProxyModel(QObject *parent = 0): QSortFilterProxyModel(parent)  {}

    void setIndices(QStringList& indices) {
        m_indices = indices;
    }
protected:
    int roleKey(const QByteArray &role) const
    {
        return roleNames().key(role, -1);
    }

    QHash<int, QByteArray> roleNames() const override
    {
        if (QAbstractItemModel *source = sourceModel())
            return source->roleNames();
        return QHash<int, QByteArray>();
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override
    {
        QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
        auto visible = true;// sourceModel()->data(sourceIndex, FilterList::Visibility);
        return qvariant_cast<bool>(visible);
    }
private:
    QStringList m_indices;
};

#endif // STOCKSPROXYMODEL_H
