#pragma once

#include <QAbstractListModel>
#include <QJsonObject>

#include "Header.h"

class HeaderList : public QAbstractListModel
{
    Q_OBJECT
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

    void addHeader(const QString &title, const QString &key, int position, int width, Header::Type type, bool visibility);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
//        if (parent.isValid())
//            return 0;
//        return 5;
//    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override{
        if (index.row() < 0 || index.row() >= m_headers.count())
            return false;

        Header* header = m_headers[index.row()];
        if(role == Filter){
            header->setFilter(value.toString());
            return true;
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

private:
//    void addStudy(Header* header, QString uuid);
//    void encode(QString& data);

private:
    QList<Header*> m_headers;
    int count_ = 0;

    QDateTime computedatetime(QString date, QString time);
    QDateTime computedatetime(QString datetime);
};

