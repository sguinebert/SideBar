#pragma once

#include <QObject>
#include <QQuickItem>
#include <QAbstractTableModel>
#include <QRegularExpression>
#include <QLineSeries>
#include <QVXYModelMapper>

#include <set>
#include <map>
#include "model/HeaderListProxy.h"
#include "model/FiltersList.h"
#include "model/Stock.h"
#include "model/DataProvider.h"
#include "model/StocksProxyModel.h"
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
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

    int m_count;

public:
    enum StockRoles {
        id = Qt::UserRole + 1,
        name,
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
        datetime,
        open,
        high,
        low,
        close,
        volume,
        //RegexFilter,
        selected
    };
    explicit TableModel(DataProvider* dataprovider, QQuickItem* chartView, QObject* parent = nullptr);
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    //Q_INVOKABLE void selectRow(int row, bool shift = false, bool ctr = false);
    
    int count() const
    {
        return m_count;
    }
    void setCount(int count)
    {
        // if (m_count == count)
        //     return;

        m_count = count;
        emit countChanged();
    }

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
    Q_INVOKABLE double getMinVal() const { return m_valmin;}
    Q_INVOKABLE double getMaxVal() const { return m_valmax;}

    Q_INVOKABLE QDateTime getDateMin() const { return m_datemin;}
    Q_INVOKABLE QDateTime getDateMax() const { return m_datemax;}

signals:
    void countChanged();
    void loadStudy(Stock *study);
private:
    void addStudy(Stock* study, std::string uuid);
    void addStock(const QString& name, QJsonObject& chart)
    {
        auto results = chart["result"].toArray();

        for(const auto& result : results) {
            auto r = result.toObject();

            auto indicators = r["indicators"].toObject();
            auto timestamp = r["timestamp"].toArray();

            auto quotes = indicators["quote"].toArray();

            for(const auto& quote : quotes) {
                auto q = quote.toObject();
                auto open = q["open"].toArray();
                auto high = q["high"].toArray();
                auto low = q["low"].toArray();
                auto close = q["close"].toArray();
                auto volume = q["volume"].toArray();

                auto meta = r["meta"].toObject();
                auto currency = meta["currency"].toString();
                auto dataGranularity = meta["dataGranularity"].toString();
                auto exchangeName = meta["exchangeName"].toString();
                auto symbol = meta["symbol"].toString();

                // auto it = m_xymaps.find(symbol.toStdString());

                for(int i(0); i < open.size(); i++) {

                    auto dtsec = timestamp[i].toInt();
                    auto datetime = QDateTime::fromSecsSinceEpoch(dtsec);
                    if(datetime < m_datemin)
                        m_datemin = datetime;

                    auto openf = open[i].toDouble();
                    auto highf = high[i].toDouble();
                    auto lowf = low[i].toDouble();
                    auto closef = close[i].toDouble();
                    auto volumef = volume[i].toInteger();

                    if(closef < m_valmin)
                        m_valmin = closef;
                    if(closef > m_valmax)
                        m_valmax = closef;

                    //qDebug() << "OHLCV : " << openf << " - " << highf << " - " << lowf << " - " << closef << " - " << volumef;
                    auto stock = new Stock(symbol, name, symbol, currency, datetime, openf, highf, lowf, closef, volumef);

                    // if(auto it = m_xymaps.find(symbol.toStdString()); it != m_xymaps.end()) { // found: add new values
                    //     auto mapper = it->second;
                    //     auto lastrow = mapper->firstRow() + mapper->rowCount();
                    //     beginInsertRows(QModelIndex(), lastrow + i, lastrow + i);
                    //     stocks_.insert(lastrow + i, stock);
                    //     endInsertRows();
                    // }
                    // else { //new stock
                        beginInsertRows(QModelIndex(), rowCount(), rowCount());
                        stocks_ << stock;
                        endInsertRows();
                    // }
                }

                if(auto it = m_xymaps.find(symbol.toStdString()); it != m_xymaps.end()) { // found: add new values
                    auto mapper = it->second;
                    auto numadded = open.size();
                    mapper->setRowCount(mapper->rowCount() + open.size());

                    while(it != m_xymaps.end()) {
                        it->second->setRowCount(it->second->rowCount() + numadded);
                        ++it;
                    }
                }
                else {
                    addSeriesToChart(symbol, rowCount() - open.size(), open.size());
                }

            }
            //auto adjclose = obj["adjclose"].toArray();
        }
        setCount(0);
        //emit onNewData();
    }
    void addSeriesToChart(QString& symbol, int firstRow, int rowCount) {

        // Now, trigger the QML function to add this series to the chart
        QVariant returnedValue;
        //QVariant var = QVariant::fromValue(symbol);
        //QString qString = QString::fromStdString(symbol);
        QMetaObject::invokeMethod(m_chartView, "addSeries", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, symbol));

        QLineSeries* lineSeries = nullptr;
        if (returnedValue.canConvert<QLineSeries*>()) {
            qDebug() << "Returned value is a QLineSeries*";
            lineSeries = qvariant_cast<QLineSeries*>(returnedValue);
            //lineSeries->setUseOpenGL(true);
            // Now you can use 'lineSeries' as needed
            //auto* series = new QLineSeries(m_chartView);
            auto* mapper = new QVXYModelMapper(m_chartView);

            m_xymaps[symbol.toStdString()] = mapper;

            auto proxy = new StocksProxyModel(symbol, this, lineSeries);

            //connect(this, &TableModel::dataChanged, proxy, &StocksProxyModel::dataChanged);

            mapper->setModel(proxy); // todo : use a proxy model to filter the rows or range ?
            mapper->setXColumn(m_xColumn);
            mapper->setYColumn(m_yColumn);
            mapper->setSeries(lineSeries);

            mapper->setFirstRow(firstRow);
            mapper->setRowCount(rowCount);

            proxy->invalidate();
            //emit mapper->rowCountChanged();
        }
    }
    // void updateRanges() {

    // }

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
    QList<Stock*> stocks_;
    std::map<std::string, QVXYModelMapper*> m_xymaps;
    //int selectedRowUp_, selectedRowDown_;
    std::set<int> selectedRows_;
    //std::vector<int> cwidths_;
    HeaderList *m_headers = 0;
    HeaderListProxy* m_headerproxy = 0;
    FiltersList *m_filters = 0;
    QHash<int, int> m_columnOrder;

    //chart and properties
    QQuickItem* m_chartView;
    int m_xColumn = 12, m_yColumn = 16;

    QLocale m_currentLocale;

    DataProvider* m_dataprovider;

    QDateTime m_datemin = QDateTime::currentDateTime(), m_datemax = QDateTime::currentDateTime();
    double m_valmin = 100000000000, m_valmax = 0;
};
