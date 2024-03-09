#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QRegularExpression>

#include <set>
#include "model/HeaderListProxy.h"
#include "model/FiltersList.h"
#include "model/Stock.h"
#include "model/DataProvider.h"
// id SERIAL PRIMARY KEY,
//     abbrev VARCHAR(255),
//     name VARCHAR(255),
//     ib_name VARCHAR(255),
//     state VARCHAR(255),
//     city VARCHAR(255)

// -- Create 'contract' table
//     CREATE TABLE contract (
//         id SERIAL PRIMARY KEY,
//         exchange_id INTEGER REFERENCES exchange(id),
//         ib_conid VARCHAR(255),
//         symbol VARCHAR(255),
//         security_type VARCHAR(255),
//         currency VARCHAR(255),
//         company VARCHAR(255),
//         industry VARCHAR(255)
//         );

// -- Create 'fundamental' table
//     CREATE TABLE fundamental (
//         contract_id INTEGER REFERENCES contract(id),
//         date DATE PRIMARY KEY,
//         market_cap NUMERIC,
//         pe_ratio NUMERIC,
//         roe NUMERIC,
//         free_cash_flow NUMERIC,
//         pb_ratio NUMERIC,
//         debt_to_equity NUMERIC,
//         eps NUMERIC,
//         ps_ratio NUMERIC,
//         dividend_yield NUMERIC
//         );
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum StockRoles {
        id = Qt::UserRole + 1,
        Name,
        ib_name,
        state,
        city,
        contract_id,
        ib_conid,
        symbol,
        security_type,
        currency,
        company,
        industry,
        //RegexFilter,
        selected
    };
    explicit TableModel(DataProvider* dataprovider = nullptr, QObject* parent = nullptr);
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

    StockRoles role(int column) {
        auto it = std::find(m_columnOrder.cbegin(), m_columnOrder.cend(), column);
        if(it != m_columnOrder.cend())
            return (StockRoles)it.key();
//        for(const auto &key : m_columnOrder.keys()) {
//            if(m_columnOrder.value(key) == column)
//                return (StudyRoles)key;
//        }
        return (StockRoles)Qt::DisplayRole;
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
    void loadStudy(Stock *study);
private:
    void addStudy(Stock* study, std::string uuid);
    QString header2string(TableModel::StockRoles role) {
        // switch (role) {
        // case TableModel::PatientName:
        //     return tr("Name");
        // case TableModel::PatientID:
        //     return tr("Patient ID");
        // case TableModel::Datetime:
        //     return tr("Date");
        // case TableModel::StudyDescription:
        //     return tr("Description");
        // case TableModel::PatientSex:
        //     return tr("Patient Sex");
        // case TableModel::PatientBirthDate:
        //     return tr("Birth Date");
        // case TableModel::Modality:
        //     return tr("Modality");
        // case TableModel::StationName:
        //     return tr("Station Name");
        // case TableModel::InstitutionName:
        //     return tr("Institution Name");
        // case TableModel::AccessionNumber:
        //     return tr("Accession Number");
        // case TableModel::PerformingPhysicianName:
        //     return tr("Performing Physician");
        // case TableModel::NameOfPhysiciansReadingStudy:
        //     return tr("Physicians Reading Study");
        // case TableModel::PerformedProcedureStepDescription:
        //     return tr("Procedure Description");
        // case TableModel::Manufacturer:
        //     return tr("Manufacturer");
        // case TableModel::BodyPartExamined:
        //     return tr("Body Part Examined");
        // case TableModel::RequestedProcedureDescription:
        //     return tr("Requested Procedure");
        // default:
        //     break;
        // }
        return "";
    }
private:
    QList<Stock*> studies_;
    std::set<std::string> uuids_;
    //int selectedRowUp_, selectedRowDown_;
    std::set<int> selectedRows_;
    //std::vector<int> cwidths_;
    HeaderList *m_headers = 0;
    HeaderListProxy* m_headerproxy = 0;
    FiltersList *m_filters = 0;
    QHash<int, int> m_columnOrder;

    QLocale m_currentLocale;

    DataProvider* m_dataprovider = nullptr;
};
