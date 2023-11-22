#pragma once

#include <QSortFilterProxyModel>

#include "HeaderList.h"


class HeaderListProxy : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    HeaderListProxy(QObject *parent = 0);

    Q_INVOKABLE int length() const;

    Q_INVOKABLE void setText(int column, QString text){
        //qDebug() << "set text : " << column << " - " << text;
        auto source = (HeaderList*)sourceModel();
        //source->test();
        //auto sourceindex = source->index(column, 0);
        auto sourceindex = mapToSource(index(column, 0));
        source->setData(sourceindex, text, HeaderList::Filter);
        //setData(index(column, 0), text, HeaderList::Filter);
//        emit source->dataChanged(sourceindex, sourceindex);
//        invalidateFilter();
        invalidate();
    }

    bool update = false;

    Q_INVOKABLE void switchColumn(int fromcolumn, int toindex)
    {
        auto sourceindex = mapToSource(index(fromcolumn, 0));
        auto source = (HeaderList*)sourceModel();

        qDebug() << "switchColumn : " << fromcolumn << " - " << toindex;

        if(fromcolumn != toindex)
            update = true;

//        for(int i = 0; i < rowCount(); i++){
//            auto sourceindex = mapToSource(index(i, 0));
//            auto position = data(index(i, 0), HeaderList::Position).toInt();
//            qDebug() << "position : " << i << " - " << sourceindex.row();
//        }
//        auto min = std::min(fromcolumn, toindex);
//        auto max = std::max(fromcolumn, toindex);

        //setData(index(fromcolumn, 0), toindex, HeaderList::Position);
        if(toindex < fromcolumn) {
            for(int i = toindex; i <= fromcolumn; i++) //i <= fromcolumn
            {

                auto visible = data(index(i, 0), HeaderList::Visibility).toBool();
                if(visible){
                    if(i == fromcolumn){
                        setData(index(i, 0), toindex, HeaderList::Position);
                    }
                    else{
                        setData(index(i, 0), i+1, HeaderList::Position);
                    }
                }
            }
        }
        else {
            for(int i = toindex; i >= fromcolumn; i--)
            {
                auto visible = data(index(i, 0), HeaderList::Visibility).toBool();
                if(visible){
                    if(i == fromcolumn){
                        setData(index(i, 0), toindex, HeaderList::Position);
                    }
                    else{
                        setData(index(i, 0), i-1, HeaderList::Position);
                    }
                }
            }
        }

        //invalidate();
//        for(int i = 0; i < rowCount(); i++){
//            auto sourceindex = mapToSource(index(i, 0));
//            auto position = data(index(i, 0), HeaderList::Position).toInt();
//            qDebug() << "position : " << i << " - " << sourceindex.row() << " - pos : " << position;
//        }
    }
    Q_INVOKABLE void setval()
    {
        qDebug() << "setval()";
        //if(update)
        invalidate();
        update = false;
    }

    int mapToSourceColumn(int proxyColumn) const {
        auto sourceindex = mapToSource(index(proxyColumn, 0));
        return sourceindex.row();
    }

    int mapFromSourceColumn(int sourceColumn) const {
        auto proxyindex = mapFromSource(index(sourceColumn, 0));
        return proxyindex.row();
    }

//    int rowCount(const QModelIndex& parent = QModelIndex()) const override
//    {
//        return sourceModel()->rowCount(parent);
//    }

protected:
    int roleKey(const QByteArray &role) const;
    QHash<int, QByteArray> roleNames() const override;

//    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override
//    {
//        // Custom comparison logic here
//        auto position = data(left, HeaderList::Position).toInt() < data(right, HeaderList::Position).toInt();
//        return position;
//    }



    //bool filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};
