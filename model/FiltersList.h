#pragma once

#include <QAbstractListModel>

#include "Filter.h"

class FiltersList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum FilterRoles {
        Section = Qt::UserRole + 1,
        Title
    };
public:
    FiltersList(QObject *parent = nullptr);

    void addFilter(const QString &section, const QString &title, const QJsonObject& json);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE Filter* get(quint32 index) const;

    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;

    Q_INVOKABLE int length() const { return m_filters.size(); }

//    void clear();

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
//    void addStudy(Header* header, QString uuid);
//    void encode(QString& data);

private:
    QList<Filter*> m_filters;
};
