#pragma once

#include <QtCore/qsortfilterproxymodel.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qjsvalue.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QRegularExpression>

#include "model/TableModel.h"

class TableModelProxy : public QSortFilterProxyModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
    //Q_PROPERTY(QObject *source READ source WRITE setSource)

    Q_PROPERTY(QByteArray sortRole READ sortRole WRITE setSortRole)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder)

    Q_PROPERTY(int sortColumn READ sortColumn WRITE setSortColumn NOTIFY sortColumnChanged)
    Q_PROPERTY(QByteArray filterRole READ filterRole WRITE setFilterRole)
    //Q_PROPERTY(QString filterString READ filterString WRITE setFilterString)
    //Q_PROPERTY(FilterSyntax filterSyntax READ filterSyntax WRITE setFilterSyntax)

    //Q_PROPERTY(QStringList strFilters READ strFilters WRITE setStrFilters NOTIFY strFiltersChanged)


    Q_ENUMS(FilterSyntax)

public:
    explicit TableModelProxy(QObject *parent = 0);

    //QObject *source() const;
    void setSource(TableModel *source);

//    QStringList strFilters() const;
//    void setStrFilters(QStringList strFilters);

    QByteArray sortRole() const;
    void setSortRole(const QByteArray &role);

    int sortColumn() const;
    void setSortColumn(const int column);

    void setSortOrder(Qt::SortOrder order);

    QByteArray filterRole() const;
    void setFilterRole(const QByteArray &role);

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole) {

//            auto cc =  m_headers->data(m_headers->index(m_headers->mapToSourceColumn(section)), HeaderList::Title).toString();
//            if(cc.isEmpty()) {
//                auto index = m_headers->mapToSourceColumn(section);
//                auto ccin = m_headers->index(index);

//                if(!ccin.isValid()) {
//                    qDebug() << "ccin is not valid";
//                }

//                auto hh =  m_headers->m_headers[index];
//                qDebug() << "cc : " << index << " - " << hh->title() << " - " << hh->key();
//            }

            if (orientation == Qt::Horizontal)
                return m_headers->data(m_headers->index(section, 0), HeaderList::Title);
            else
                return QString("ver-%1").arg(section);

//            if (orientation == Qt::Horizontal)
//                return m_headers->data(m_headers->index(m_headers->mapToSourceColumn(section)), HeaderList::Title);
//            else
//                return QString("ver-%1").arg(section);
        }
        return QVariant();

        //return m_source->headerData(section, orientation, role);
    }

//    QString filterString() const;
//    void setFilterString(const QString &filter);

    Q_INVOKABLE void switchColumn(int from, int to)
    {
        m_headers->switchColumn(from, to);
    }
    Q_INVOKABLE void updateColumn()
    {
        //invalidate(); //TODO: find correct workaround to fix this
        m_headers->invalidate();
        invalidate(); //invalidate because of header change
    }

    Q_INVOKABLE void selectRow(int row, bool shift = false, bool ctr = false);
    Q_INVOKABLE void setFilters();
    //Q_INVOKABLE void setFilterStr(int index, const QString& filter);
    Q_INVOKABLE void setDatetimeRange(QDateTime minDate, QDateTime maxDate) {
        qDebug() << "setDatetimeRange : " << minDate << " - " << maxDate;
        m_minDate = minDate;
        m_maxDate = maxDate;
        invalidateFilter();
    }
    Q_INVOKABLE void clearDatetimeRange() {
        m_minDate = QDateTime();
        m_maxDate = QDateTime();
        invalidateFilter();
    }
    Q_INVOKABLE void setDate(QDate date) {
        qDebug() << "setDate : " << date;
        m_date = date;
        invalidateFilter();
    }
    Q_INVOKABLE void clearDateRange() {

        m_date = QDate();
        qDebug() << "clearDateRange : " << m_date;
        invalidateFilter();
    }

    Q_INVOKABLE void selectFilter(int index){
        m_source->selectFilter(index);
        invalidateFilter();
    }

    Q_INVOKABLE int checktype(int column);
    Q_INVOKABLE void headerclick(int column);

    void setColumnOrder(const QVector<int>& newOrder) {
        //m_headers->setColumnOrder(newOrder);
        invalidate(); // Refresh the proxy model
    }

    enum FilterSyntax {
        RegExp,
        Wildcard,
        FixedString
    };


    //int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    int count() const;
    int length() const;
    Q_INVOKABLE QJSValue get(int index) const;

    void classBegin() override;
    void componentComplete() override;

signals:
    void countChanged();
    void lengthChanged();
    void sortColumnChanged();
//    void strFiltersChanged();

    void newRequest(QJsonObject obj);
    void popupDateTime();
    void popupDate();
    void popupModality();
protected:
    int roleKey(const QByteArray &role) const;
    QHash<int, QByteArray> roleNames() const override;

    bool filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override {
        if (!proxyIndex.isValid())
            return QVariant();


        QModelIndex sourceIndex = mapToSource(proxyIndex);
        //QModelIndex sourceIndex = mapToSource(this->index(proxyIndex.row(), mapToSourceColumn(proxyIndex.column())));
        return sourceModel()->data(sourceIndex, role);
    }

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override {
        return sourceModel()->index(proxyIndex.row(), m_headers->mapToSourceColumn(proxyIndex.column()));
    }

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override {
        int proxyColumn = m_headers->mapFromSourceColumn(sourceIndex.column());// columnOrder.indexOf(sourceIndex.column());
        return index(sourceIndex.row(), proxyColumn >= 0 ? proxyColumn : sourceIndex.column());
    }

private:
    bool datetimeInRange(const QDateTime& datetime) const
    {
        return (!m_minDate.isValid() || datetime > m_minDate)
                && (!m_maxDate.isValid() || datetime < m_maxDate);
    }
    bool dateInRange(const QDate& date) const
    {
        return (!m_date.isValid() || date == m_date);
    }

private:
    mutable TableModel* m_source = 0;
    HeaderListProxy* m_headers = 0;
    bool m_complete;
    bool search_;
    int selectedRowUp_, selectedRowDown_, baserow_;
    //std::set<int> selectedRows_;
    QByteArray m_sortRole;
    QByteArray m_filterRole;
    int m_sortColumn;
    Qt::SortOrder sortOrder_;

    QDateTime m_minDate, m_maxDate;
    QDate m_date;

    //QVector<int> columnOrder;
};
