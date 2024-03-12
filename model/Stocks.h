#pragma once

#include <QObject>
#include <QAbstractListModel>

#include "model/DataProvider.h"
#include "model/Stock.h"

class Stocks : public QAbstractListModel
{
	Q_OBJECT

public:
    enum StocksRoles {
        id = Qt::UserRole + 1,
        name,
        country,
        symbol,
        currency,
        founded,
        employees,
        industries,
        indices,
        industry,
        symbols
	};
    explicit Stocks(DataProvider* dataprovider, QObject* parent = 0);
    ~Stocks();


//	void addSerie(Volume* volume, QString useruuid, QString studyuuid, QString serieuuid, QString studyDescription, QString report);
//	void addSerie(Volume* volume, QString studyDescription, QString nip, QString useruuid, QString studyuuid, QString serieuuid, QString date, QString time);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


    Q_INVOKABLE Stock* get(quint32 index) const;

	void clear();
	Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;

    Q_INVOKABLE void getData(quint32 index)
    {
        if (index  >= m_stocks.size())
            return;
        //auto de = conversations_[index];
        auto name = m_stocks[index]->name();
        auto symbols = m_stocks[index]->symbols();
        // if(symbols.isEmpty())
        //     return;
        auto obj = symbols[0].toObject();
        auto currency = obj["currency"].toString();
        auto yahoo = obj["yahoo"].toString();
        m_dataprovider->getStockHistory(name, yahoo, QDateTime::currentDateTime().addDays(-1000));
    }

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    void addStock(Stock* stock/*, QString uuid*/);
	void encode(QString& data);
private:
    QList<Stock*> m_stocks;
    DataProvider* m_dataprovider;
    //int severalPatient_;
    //std::map<QString, int> patientMap_;
    //std::map<QString, Stock*> studyMap_;
    //std::map<QString, Volume*> serieMap_;

	QDateTime computedatetime(QString date, QString time);
	QDateTime computedatetime(QString datetime);

};
