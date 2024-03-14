#ifndef STOCKSPROXYMODEL_H
#define STOCKSPROXYMODEL_H
#include <QObject>
#include <QSortFilterProxyModel>
#include <QDateTime>

#include "model/TableModel.h"

class StocksProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    StocksProxyModel(TableModel* tablemodel, QObject *parent = 0): QSortFilterProxyModel(parent), m_tablemodel(tablemodel)  {}

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
        if(m_symbol.isEmpty())
            return true;

        QModelIndex sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
        auto visible = m_symbol == sourceModel()->data(sourceIndex, 264);// sourceModel()->data(sourceIndex, FilterList::Visibility);
        return visible;
    }

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
    {
        // Obtenez les valeurs pour la colonne "symbol" de chaque élément
        auto leftSymbol = sourceModel()->data(sourceModel()->index(left.row(), 0, left.parent())).toString();
        auto rightSymbol = sourceModel()->data(sourceModel()->index(right.row(), 0, right.parent())).toString();

        // Compare d'abord les symboles
        if (leftSymbol < rightSymbol)
            return true;
        if (leftSymbol > rightSymbol)
            return false;

        // Si les symboles sont égaux, compare les dates
        QVariant leftDateTime = sourceModel()->data(sourceModel()->index(left.row(), 12, left.parent()));
        QVariant rightDateTime = sourceModel()->data(sourceModel()->index(right.row(), 12, right.parent()));

        QDateTime leftDate = leftDateTime.toDateTime();
        QDateTime rightDate = rightDateTime.toDateTime();

        return leftDate < rightDate;
    }


private:
    TableModel* m_tablemodel;
    QStringList m_indices;
    QString m_symbol;
};

#endif // STOCKSPROXYMODEL_H
