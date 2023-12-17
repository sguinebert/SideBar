#pragma once

#include <QAbstractListModel>
#include <QJsonObject>

#include "Header.h"

class HeaderList : public QAbstractListModel
{
    Q_OBJECT
    friend class TableModelProxy;
public:
    enum HeaderRoles {
        Type = Qt::UserRole + 1,
        Title,
        Width,
        Visibility,
        Position,
        Filter,
        RegexFilter
    };
public:
    HeaderList(QObject* parent = nullptr);

    void addHeader(const QString &title, const QString &key, int sourceIndex, int position, int width, Header::Type type, bool visibility);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
    {
        if (index.row() < 0 || index.row() >= m_headers.count())
            return false;

        Header* header = m_headers[index.row()];

        switch (role) {
        case Filter:
            header->setFilter(value.toString());
            return true;
        case Position:
            header->setPosition(value.toInt());
            return true;
        case Width:
            header->setWidth(value.toInt());
            return true;
        default:
            break;
        }
        return false;
    }
    void setFilters(const QJsonObject& jfilters) {
        for(auto header : std::as_const(m_headers)) {
            bool contain(false);
            for(auto &key : jfilters.keys()){
                if(key.contains(header->key(), Qt::CaseInsensitive)){
                    contain = true;
                    header->setFilter(jfilters.value(key).toString());
                }
            }
            if(!contain)
                 header->setFilter("");
        }
    }

    Q_INVOKABLE Header* get(quint32 index) const;

    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;

    Q_INVOKABLE int length() const { return m_headers.size(); }


    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

    void setColumnOrder(const QVector<int>& newOrder) {
        m_columnOrder = newOrder;
        //invalidate(); // Refresh the proxy model
    }

    int mapToSourceColumn(int proxyColumn) const {
        if (proxyColumn >= 0 && proxyColumn < m_columnOrder.size())
            return m_columnOrder[proxyColumn];
        return proxyColumn; // Fallback to default order
    }

    int mapFromSourceColumn(int sourceColumn) const {
        return m_columnOrder.indexOf(sourceColumn);
    }

private:
//    void addStudy(Header* header, QString uuid);
//    void encode(QString& data);

private:
    QList<Header*> m_headers;
    int count_ = 0;
    QVector<int> m_columnOrder;

    QDateTime computedatetime(QString date, QString time);
    QDateTime computedatetime(QString datetime);
};

