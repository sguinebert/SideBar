#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QRegularExpression>

#include <set>
#include "model/HeaderListProxy.h"
#include "model/FiltersList.h"
#include "model/Study.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum StudyRoles {
        Uuid = Qt::UserRole + 1,
        Name,
        Pid,
        PatientSex,
        PatientBirthDate,
        Datetime,
        StudyID,
        StudyInstanceUID,
        AccessionNumber,
        Modality,
        InstitutionName,
        Manufacturer,
        StationName,
        StudyDescription,
        RequestedProcedureDescription,
        BodyPartExamined,

        PerformingPhysicianName,
        NameOfPhysiciansReadingStudy,
        PerformedProcedureStepDescription,
        ReferringPhysicianName,

        StudyNumber,
        Series,
        //RegexFilter,
        selected
    };
    explicit TableModel(QObject* parent = nullptr);
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    //Q_INVOKABLE void selectRow(int row, bool shift = false, bool ctr = false);
    
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void setSelected(const std::set<int>& selectedRows)
    {
        selectedRows_ = selectedRows;
    }
    void emplaceSelection(int row) {
        selectedRows_.emplace(row);
    }
    void clearSelection() {
        selectedRows_.clear();
    }

    QRegularExpression regex(int column) {
        column = m_columnOrder[column];
        //qDebug() << "filter1 : " << column << " - " << m_headerproxy->mapToSource(m_headerproxy->index(column, 0)).row() << " - " << qvariant_cast<QRegularExpression>(m_headers->data(m_headerproxy->mapToSource(m_headerproxy->index(column, 0)), HeaderList::RegexFilter));
        return  qvariant_cast<QRegularExpression>(m_headers->data(m_headerproxy->mapToSource(m_headerproxy->index(column, 0)), HeaderList::RegexFilter));
    }
    QString filter(int column) {
        column = m_columnOrder[column];
        return  qvariant_cast<QString>(m_headers->data(m_headerproxy->mapToSource(m_headerproxy->index(column, 0)), HeaderList::Filter));
    }

    void query() {
        qDebug() << "deport the query stuff to headerlist model ";

        {
//            QJsonObject obj;
//            obj["query"] = "studies";
//            obj["name"] = strFilters_[0];
//            obj["pid"] = strFilters_[1];
//            obj["datetime"] = strFilters_[2];
//            obj["description"] = strFilters_[3];
//            emit newRequest(obj);
        }
    }

    void addFilter(QJsonObject json);
   
    void addStudy(QJsonObject json);

    QHash<int, QByteArray> roleNames() const override;

    StudyRoles role(int column) {
        auto it = std::find(m_columnOrder.cbegin(), m_columnOrder.cend(), column);
        if(it != m_columnOrder.cend())
            return (StudyRoles)it.key();
//        for(const auto &key : m_columnOrder.keys()) {
//            if(m_columnOrder.value(key) == column)
//                return (StudyRoles)key;
//        }
        return (StudyRoles)Qt::DisplayRole;
    }

    Header::Type type(int column) const {
        auto index = m_headerproxy->index(column, 0);
        auto type = m_headerproxy->data(index, HeaderList::Type);
        return (Header::Type)qvariant_cast<int>(type);
    }
    bool visible(int column) const {
        auto index = m_headers->index(column, 0);

//        auto index2 = m_headerproxy->index(column, 0);
//        auto cc = m_headerproxy->mapToSource(index);
//        qDebug() << "column : " << column << " - " << index2.row() << " - " << index.row() << " => " << m_headerproxy->data(index2, HeaderList::Visibility);

        auto visibility = m_headers->data(index, HeaderList::Visibility);
        return qvariant_cast<bool>(visibility);
    }

//    Q_INVOKABLE int width(int column) const { return cwidths_[column]; }
//    Q_INVOKABLE void setWidth(int column, int width) { cwidths_[column] = width; }
    Q_INVOKABLE void loadstudy(int index);

    Q_INVOKABLE void selectFilter(int index);

    HeaderList* headers() const { return m_headers; }
    HeaderListProxy* headerproxy() const { return m_headerproxy; }
    FiltersList* filters() const { return m_filters; }

signals:
    void loadStudy(Study *study);
private:
    void addStudy(Study* study, std::string uuid);
private:
    QList<Study*> studies_;
    std::set<std::string> uuids_;
    //int selectedRowUp_, selectedRowDown_;
    std::set<int> selectedRows_;
    //std::vector<int> cwidths_;
    HeaderList *m_headers = 0;
    HeaderListProxy* m_headerproxy = 0;
    FiltersList *m_filters = 0;
    QHash<int, int> m_columnOrder;

    QLocale m_currentLocale;
};
