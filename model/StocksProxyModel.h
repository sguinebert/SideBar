#ifndef STOCKSPROXYMODEL_H
#define STOCKSPROXYMODEL_H
#include <QObject>
#include <QSortFilterProxyModel>
#include <QDateTime>


class TableModel;

class StocksProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    StocksProxyModel(const QString& symbol, TableModel* tablemodel, QObject *parent = 0):
        QSortFilterProxyModel(parent),
        m_tablemodel(tablemodel),
        m_symbol(symbol)
    {
        // connect(this, &QSortFilterProxyModel::rowsInserted, this, &StocksProxyModel::);
        // connect(this, &QSortFilterProxyModel::rowsRemoved, this, &StocksProxyModel::countChanged);
        setFilterCaseSensitivity(Qt::CaseInsensitive);
        setSortCaseSensitivity(Qt::CaseInsensitive);
        setDynamicSortFilter(true);
        sort(0, Qt::AscendingOrder);

    }

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

    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override {
        //qDebug() << "StocksProxyModel::data()";
        if (!proxyIndex.isValid())
            return QVariant();


        QModelIndex sourceIndex = mapToSource(proxyIndex);
        //QModelIndex sourceIndex = mapToSource(this->index(proxyIndex.row(), mapToSourceColumn(proxyIndex.column())));
        return sourceModel()->data(sourceIndex, role);
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    TableModel* m_tablemodel;
    QStringList m_indices;
    QString m_symbol;
};

#endif // STOCKSPROXYMODEL_H
