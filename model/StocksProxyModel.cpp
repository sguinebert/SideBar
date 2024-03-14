#include "StocksProxyModel.h"

#include "model/TableModel.h"

bool StocksProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    qDebug() << "filter test ";
    return true;
    if(m_symbol.isEmpty())
        return true;

    QModelIndex sourceIndex = m_tablemodel->index(sourceRow, 0, sourceParent);
    auto visible = m_symbol == m_tablemodel->data(sourceIndex, TableModel::symbol).toString();// sourceModel()->data(sourceIndex, FilterList::Visibility);
    return visible;
}

// bool StocksProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
// {
//     // Obtenez les valeurs pour la colonne "symbol" de chaque élément
//     // auto left = m_tablemodel->index(left.row(), 0, left.parent());
//     // m_tablemodel->index(right.row(), 0, right.parent());


//     auto leftSymbol = m_tablemodel->data(left, TableModel::symbol).toString();
//     auto rightSymbol = m_tablemodel->data(right, TableModel::symbol).toString();

//     // Compare d'abord les symboles
//     if (leftSymbol < rightSymbol)
//         return true;
//     if (leftSymbol > rightSymbol)
//         return false;

//     // Si les symboles sont égaux, compare les dates
//     QVariant leftDateTime = m_tablemodel->data(left, TableModel::datetime);
//     QVariant rightDateTime = m_tablemodel->data(right, TableModel::datetime);

//     QDateTime leftDate = leftDateTime.toDateTime();
//     QDateTime rightDate = rightDateTime.toDateTime();

//     return leftDate < rightDate;
// }
