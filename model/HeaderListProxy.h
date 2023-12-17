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

    Q_INVOKABLE void setColumnWidth(int column, int width)
    {
        setData(index(column, 0), width, HeaderList::Width);
    }

    Q_INVOKABLE int columnWidthProvider(int column) const
    {
        return data(index(column, 0), HeaderList::Width).toInt();
    }

//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
//    {
//        return false;
//    }

    Q_INVOKABLE void switchColumn(int fromcolumn, int toindex)
    {
        qDebug() << "switchColumn : " << fromcolumn << " - " << toindex;

        for(int i(0); i < 7; i++)
            qDebug() << "setval()" << data(index(i, 0), HeaderList::Position)
                     << " - " << data(index(i, 0), HeaderList::Title);

//        for(int i = 0; i < rowCount(); i++){
//            auto sourceindex = mapToSource(index(i, 0));
//            auto position = data(index(i, 0), HeaderList::Position).toInt();
//            qDebug() << "position : " << i << " - " << sourceindex.row();
//        }
//        auto min = std::min(fromcolumn, toindex);
//        auto max = std::max(fromcolumn, toindex);

        std::vector<int> modified;

        //setData(index(fromcolumn, 0), toindex, HeaderList::Position);
        if(toindex < fromcolumn) {
            for(int i = toindex; i <= fromcolumn; i++) //i <= fromcolumn
            {
                auto visible = data(index(i, 0), HeaderList::Visibility).toBool();
                if(visible){
                    if(i == fromcolumn){
                        //setData(index(i, 0), toindex, HeaderList::Position);
                        for(int ii(0); ii < rowCount(); ii++)
                        {
                            auto position = data(index(ii, 0), HeaderList::Position).toInt();
                            if(position == i && std::find(modified.begin(), modified.end(), ii) == modified.end()) {
                                modified.push_back(ii);
                                setData(index(ii, 0), toindex, HeaderList::Position);
                            }
                        }
                    }
                    else{
                        //setData(index(i, 0), i+1, HeaderList::Position);
                        for(int ii(0); ii < rowCount(); ii++)
                        {
                            auto position = data(index(ii, 0), HeaderList::Position).toInt();
                            if(position == i && std::find(modified.begin(), modified.end(), ii) == modified.end()) {
                                modified.push_back(ii);
                                setData(index(ii, 0), i+1, HeaderList::Position);
                            }
                        }
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
                        //setData(index(i, 0), toindex, HeaderList::Position);
                        for(int ii(0); ii < rowCount(); ii++)
                        {
                            auto position = data(index(ii, 0), HeaderList::Position).toInt();
                            if(position == i && std::find(modified.begin(), modified.end(), ii) == modified.end()) {
                                modified.push_back(ii);
                                setData(index(ii, 0), toindex, HeaderList::Position);
                            }
                        }
                    }
                    else{
                        //setData(index(i, 0), i-1, HeaderList::Position);
                        for(int ii(0); ii < rowCount(); ii++)
                        {
                            auto position = data(index(ii, 0), HeaderList::Position).toInt();
                            if(position == i && std::find(modified.begin(), modified.end(), ii) == modified.end()) {
                                modified.push_back(ii);
                                setData(index(ii, 0), i-1, HeaderList::Position);
                            }
                        }
                    }
                }
            }
        }


        for(int i(0); i < 7; i++)
            qDebug() << "corrected val()" << data(index(i, 0), HeaderList::Position)
                     << " - " << data(index(i, 0), HeaderList::Title);

//        invalidate();
//        for(int i = 0; i < rowCount(); i++){
//            auto sourceindex = mapToSource(index(i, 0));
//            auto position = data(index(i, 0), HeaderList::Position).toInt();
//            qDebug() << "position : " << i << " - " << sourceindex.row() << " - pos : " << position;
//        }
    }
    Q_INVOKABLE void setval()
    {


        invalidate();

//        for(int i(0); i < 7; i++)
//            qDebug() << "setval()" << data(index(i, 0), HeaderList::Position)
//                     << " - " << data(index(i, 0), HeaderList::Title);

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
    //bool filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};
