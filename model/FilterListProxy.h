#ifndef FILTERLISTPROXY_H
#define FILTERLISTPROXY_H

#include <QSortFilterProxyModel>
#include <QObject>

#include "FiltersList.h"

class FilterListProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
   FilterListProxy(QObject *parent = 0);

    Q_INVOKABLE int length() const;

//    Q_INVOKABLE void setText(int column, QString text){
//        //qDebug() << "set text : " << column << " - " << text;
//        auto source = (FiltersList*)sourceModel();
//        //source->test();
//        //auto sourceindex = source->index(column, 0);
//        auto sourceindex = mapToSource(index(column, 0));
//        source->setData(sourceindex, text, FiltersList::Filter);
//        //setData(index(column, 0), text, HeaderList::Filter);
//        //        emit source->dataChanged(sourceindex, sourceindex);
//        //        invalidateFilter();
//        invalidate();
//    }

protected:
    int roleKey(const QByteArray &role) const;
    QHash<int, QByteArray> roleNames() const override;

    //bool filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // FILTERLISTPROXY_H
