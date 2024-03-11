#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <string_view>

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>

const QString yahooAPI = "https://query2.finance.yahoo.com/v8/finance/chart/";

constexpr std::string_view createDB = R"""(
-- Create 'exchange' table
CREATE TABLE exchange (
    id SERIAL PRIMARY KEY,
    abbrev VARCHAR(255),
    name VARCHAR(255),
    ib_name VARCHAR(255),
    state VARCHAR(255),
    city VARCHAR(255)
);

-- Create 'contract' table
CREATE TABLE contract (
    id SERIAL PRIMARY KEY,
    exchange_id INTEGER REFERENCES exchange(id),
    ib_conid VARCHAR(255),
    symbol VARCHAR(255),
    security_type VARCHAR(255),
    currency VARCHAR(255),
    company VARCHAR(255),
    industry VARCHAR(255)
);

-- Create 'price_volume' table
CREATE TABLE price_volume (
    contract_id INTEGER REFERENCES contract(id),
    date_time TIMESTAMPTZ NOT NULL,
    open NUMERIC,
    high NUMERIC,
    low NUMERIC,
    close NUMERIC,
    volume BIGINT
);

-- Create 'fundamental' table
CREATE TABLE fundamental (
    contract_id INTEGER REFERENCES contract(id),
    date DATE PRIMARY KEY,
    market_cap NUMERIC,
    pe_ratio NUMERIC,
    roe NUMERIC,
    free_cash_flow NUMERIC,
    pb_ratio NUMERIC,
    debt_to_equity NUMERIC,
    eps NUMERIC,
    ps_ratio NUMERIC,
    dividend_yield NUMERIC
);
)""";

/*Insert an exchange
 *('NYSE', 'New York Stock Exchange', 'NYSE', 'New York', 'New York')
 */
constexpr
    std::string_view insertexchange = "INSERT INTO exchange (abbrev, name, ib_name, state, city) VALUES"
      "(?, ?, ?, ?, ?)";


/*-- Get the ID of the exchange we just inserted to use in the contract table
 * -- Insert a stock contract
 * (1, '123456', 'AAPL', 'Stock', 'USD', 'Apple Inc.', 'Technology')
 */

constexpr
    std::string_view insertcontract =
    "INSERT INTO contract (exchange_id, ib_conid, symbol, security_type, currency, company, industry) VALUES"
    "(?, ?, ?, ?, ?, ?, ?)";

/*Insert a price ... volume
 *(1, '2024-03-07 09:30:00', 100.00, 105.00, 99.00, 104.00, 1000000)
 */
constexpr
    std::string_view insertprice = "INSERT INTO price_volume (contract_id, date_time, open, high, low, close, volume) VALUES"
                            "(?, ?, ?, ?, ?, ?, ?)";


//-- Convert the 'price_volume' table into a hypertable
//std::string_view createHyperTable = "SELECT create_hypertable('price_volume', 'date_time')";
//provide data via SQLITE or Postgresql or CSV (load to sql) or URL (our server to access a protected database)
class DataProvider : public QObject
{
    Q_OBJECT
public:
    DataProvider()
    {

    }

    void loadFromCSV(std::string_view path){

    }

    void createPgTables() {
        m_db = QSqlDatabase::addDatabase("QPSQL"); // Or use the connection name if you've already set it up
        m_db.setHostName(m_host);
        m_db.setDatabaseName(m_dbname);
        m_db.setUserName(m_user);
        m_db.setPassword(m_password);

        if (!m_db.open()) {
            qDebug() << "Database connection failed: " << m_db.lastError().text();
            return;
        }

        QSqlQuery query;

        // Create 'exchange' table
        query.exec("CREATE TABLE exchange ("
                   "id SERIAL PRIMARY KEY,"
                   "abbrev VARCHAR(255),"
                   "name VARCHAR(255),"
                   "ib_name VARCHAR(255),"
                   "state VARCHAR(255),"
                   "city VARCHAR(255));");

        // Create 'contract' table
        query.exec("CREATE TABLE contract ("
                   "id SERIAL PRIMARY KEY,"
                   "exchange_id INTEGER REFERENCES exchange(id),"
                   "ib_conid VARCHAR(255),"
                   "symbol VARCHAR(255),"
                   "security_type VARCHAR(255),"
                   "currency VARCHAR(255),"
                   "company VARCHAR(255),"
                   "industry VARCHAR(255));");

        // Ensure TimescaleDB extension is enabled
        query.exec("CREATE EXTENSION IF NOT EXISTS timescaledb CASCADE;");

        // Create 'price_volume' hypertable
        query.exec("CREATE TABLE price_volume ("
                   "contract_id INTEGER REFERENCES contract(id),"
                   "date_time TIMESTAMPTZ NOT NULL,"
                   "open NUMERIC,"
                   "high NUMERIC,"
                   "low NUMERIC,"
                   "close NUMERIC,"
                   "volume BIGINT);");

        // Convert 'price_volume' to hypertable
        query.exec("SELECT create_hypertable('price_volume', 'date_time');");

        // Check for errors
        if (query.lastError().isValid()) {
            qDebug() << "SQL error: " << query.lastError().text();
        } else {
            qDebug() << "Tables created successfully!";
        }

        //m_db.close();
    }
    void createSqliteTables() {
        m_db = QSqlDatabase::addDatabase("sqlite"); // Or use the connection name if you've already set it up
        m_db.setHostName(m_host);
        m_db.setDatabaseName(m_dbname);

        if (!m_db.open()) {
            qDebug() << "Database connection failed: " << m_db.lastError().text();
            return;
        }

        QSqlQuery query;

        // Create db
        query.exec(createDB.data());

        // Check for errors
        if (query.lastError().isValid()) {
            qDebug() << "SQL error: " << query.lastError().text();
        } else {
            qDebug() << "Tables created successfully!";
        }

        //m_db.close();
    }

    QJsonArray getHeaderConfig()
    {
        if(m_db.open())
        {
            //m_db.
        }
        return QJsonArray();
    }

    inline QJsonObject getStocksSymbols()
    {
        QFile jsonfile(":/data/stocks_symbols.json");
        jsonfile.open(QIODevice::ReadOnly|QIODevice::Text);
        QByteArray data = jsonfile.readAll();
        jsonfile.close();

        QJsonParseError errorPtr;
        QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
        if (doc.isNull()) {
            qDebug() << "Parse failed "  << errorPtr.offset << " - " << errorPtr.errorString();
            return QJsonObject();
        }
        QJsonObject rootObj = doc.object();

        // QFile file("stock_nice.json");
        // if (file.open(QIODevice::WriteOnly)) {
        //     file.write(doc.toJson());
        //     file.close();
        //     qDebug() << "Stock data downloaded successfully!";
        // } else {
        //     qDebug() << "Failed to open file for writing";
        // }

        return rootObj;
    }

    void getStockHistory(QString name,
                         QString symbol,
                         QDateTime startTime,
                         QDateTime endTime = QDateTime::currentDateTime(),
                         QString interval = "1d")
    {
        symbol = "AAPL"; // Replace with desired stock symbol
        // Handle time zone offset if necessary (consider UTC)
        // QTimeZone timeZone = startTime.timeZone();

        // Convert to epoch seconds (adjust units if needed)
        qint64 startTimeInEpochSeconds = startTime.toSecsSinceEpoch();
        qint64 endTimeInEpochSeconds = endTime.toSecsSinceEpoch();
        QString period1 = QString::number(startTimeInEpochSeconds); // Starting time in epoch seconds (needs conversion)
        QString period2 = QString::number(endTimeInEpochSeconds); // Ending time in epoch seconds (needs conversion)
         // Adjust for desired interval (e.g., "1d" for daily, "1m" for 1 minute)

        QString queryString = QString("?symbol=%1&period1=%2&period2=%3&interval=%4")
                                  .arg(symbol)
                                  .arg(period1)
                                  .arg(period2)
                                  .arg(interval);

        QString url = yahooAPI + queryString;

        qDebug() << "URL : " << url;
        downloadStockData(url, name, symbol);
    }

    void parseOHLCV(QJsonObject& obj, const QString& name)
    {

        auto chart = obj["chart"].toObject();

        if(!chart["error"].isNull()) {
            qDebug() << "Error : " << chart;
            return;
        }

        emit dataReceived(name, chart);

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

                for(int i(0); i < open.size(); i++) {

                    auto dtsec = timestamp[i].toInt();
                    auto datetime = QDateTime::fromSecsSinceEpoch(dtsec);

                    auto openf = open[i].toDouble();
                    auto highf = high[i].toDouble();
                    auto lowf = low[i].toDouble();
                    auto closef = close[i].toDouble();
                    auto volumef = volume[i].toInteger();

                    qDebug() << "OHLCV : " << openf << " - " << highf << " - " << lowf << " - " << closef << " - " << volumef;
                }

            }

            auto meta = r["meta"].toObject();
            auto currency = meta["currency"].toString();
            auto dataGranularity = meta["dataGranularity"].toString();
            auto exchangeName = meta["exchangeName"].toString();
            auto symbol = meta["symbol"].toString();


            //auto adjclose = obj["adjclose"].toArray();
        }


    }

    void downloadStockData(const QString& url, const QString& name, const QString& symbol) {
        QNetworkAccessManager* manager = new QNetworkAccessManager();
        QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));

        connect(reply, &QNetworkReply::finished, [this, reply, name, symbol]() {
            if (reply->error() == QNetworkReply::NoError) {

                QJsonParseError error;
                QJsonDocument document = QJsonDocument::fromJson(reply->readAll(), &error);

                if (!document.isEmpty()) {
                    if (document.isObject()) {
                        auto object = document.object();
                        this->parseOHLCV(object, name);
                        //qDebug() << "object : " << object;
                        // Access object elements here using keys (e.g., object["key"])
                    } else {
                        qDebug() << "Error: Expected a JSON object, but got a "
                                  << ".";
                        // Handle other document types (if not an object)
                    }
                } else {
                    qDebug() << "Error parsing JSON: " << error.errorString();
                    // Handle parsing error
                }

                QFile file(symbol + ".json");
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(document.toJson());
                    file.close();
                    qDebug() << "Stock data downloaded successfully!";
                } else {
                    qDebug() << "Failed to open file for writing";
                }
            } else {
                qDebug() << "Download error:" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
signals:
    void dataReceived(const QString&, QJsonObject& obj);

private:
    QSqlDatabase m_db;
    QString m_host;
    QString m_dbname;
    QString m_user;
    QString m_password;

};


#endif // DATAPROVIDER_H
