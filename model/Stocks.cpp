#include "Stocks.h"

Stocks::Stocks(DataProvider* dataprovider, QObject *parent) :
    QAbstractListModel(parent),
    m_dataprovider(dataprovider)
{
    auto stockslist = m_dataprovider->getStocksSymbols();
    auto companies = stockslist["companies"].toArray();

    for(const auto& company : companies) {
        auto comp = company.toObject();
        auto name = comp["name"].toString();
        auto symbol = comp["symbol"].toString();
        auto country = comp["country"].toString();

        auto industries = comp["industries"].toArray();
        QString concatindustry;
        for(const auto&industry : industries)
        {
            auto ids = industry.toString();
            if(!concatindustry.isEmpty())
                concatindustry.append(", ");
            concatindustry.append(ids);
        }

        //indices
        auto indices = comp["indices"].toArray();
        auto indicesstr = indices.toVariantList();
        //indicesstr.to

        //metadata
        auto metadata = comp["metadata"].toObject();
        auto employees = metadata["employees"].toInt();
        auto founded = metadata["founded"].toInt();

        //symbols used by internet data providers
        auto symbols = comp["symbols"].toArray();
        for(const auto& sym : symbols) {
            auto s = sym.toObject();
            auto currency = s["currency"].toString();
            auto google = s["google"].toString();
            auto yahoo = s["yahoo"].toString();
        }
        //ring id, QString name, QString country, QString symbol, QString currency, QObject *paren
        auto stock = new Stock(symbol, name, country, symbol, "US", concatindustry, this);
        addStock(stock);
        //m_stocks.emplaceBack(stock);
    }
    qDebug() << "m_stocks num : " << m_stocks.size();

}

Stocks::~Stocks()
{
}

void Stocks::addStock(Stock* stock/*, QString uuid*/)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_stocks << stock;
    endInsertRows();
    //studyMap_.emplace(uuid, stock);
}
void Stocks::encode(QString& data)
{
    data.replace("&amp;", "&");
    data.replace("&quot;", "\"");
    data.replace("&apos;", "\'");
    data.replace("&lt;", "<");
    data.replace("&gt;", ">");
    data.replace("&#39;", "'");
    data.replace("<br />", "");
    data.replace("<br>", "");
}
//void Studies::addSerie(Volume* volume, QString useruuid, QString studyuuid, QString serieuuid, QString studyDescription, QString report)
//{
//    auto it0 = serieMap_.find(serieuuid);
//    if (it0 == serieMap_.end()) {
//        auto itp = patientMap_.find(volume->nip());
//        int pid(0);
//        if (itp == patientMap_.end()) {
//            pid = severalPatient_;
//            patientMap_.emplace(volume->nip(), severalPatient_);
//            severalPatient_++;
//        }
//        else
//            pid = itp->second;
//        serieMap_.emplace(serieuuid, volume);
//        auto it1 = studyMap_.find(studyuuid);
//        if (it1 == studyMap_.end()) {
//            //auto datetime = computedatetime(date, time);
//            //encode(report);
//            auto study = new Study(pid, volume->name(), studyDescription, useruuid, studyuuid, volume->datetime(), this, report);
//            addStudy(study, studyuuid);

//            study->appendSerie(volume);
//        }
//        else {
//            auto study = it1->second;
//            study->appendSerie(volume);
//        }
//    }
//}

//void Studies::addSerie(Volume* volume, QString studyDescription, QString nip, QString useruuid, QString studyuuid, QString serieuuid, QString date, QString time)
//{
//    auto it0 = serieMap_.find(serieuuid);
//    if (it0 == serieMap_.end()) {
//        auto itp = patientMap_.find(nip);
//        int pid(0);
//        if (itp == patientMap_.end()) {
//            pid = severalPatient_;
//            patientMap_.emplace(nip, severalPatient_);
//            severalPatient_++;
//        }
//        else
//            pid = itp->second;
//        serieMap_.emplace(serieuuid, volume);
//        auto it1 = studyMap_.find(studyuuid);
//        if (it1 == studyMap_.end()) {
//            auto datetime = computedatetime(date, time);
//            auto study = new Study(pid, volume->name(), studyDescription, useruuid, studyuuid, datetime, this);
//            addStudy(study, studyuuid);

//            study->appendSerie(volume);
//        }
//        else {
//            auto study = it1->second;
//            study->appendSerie(volume);
//        }
//    }
//}

int Stocks::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
    return m_stocks.count();
}

QVariant Stocks::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_stocks.count())
        return QVariant();

    const Stock* stock = m_stocks[index.row()];

    switch (role) {
    case id:
        return stock->id();
        break;
    case name:
        return stock->name();
        break;
    case country:
        return stock->country();
        break;
    case symbol:
        return stock->symbol();
        break;
    case founded:
        return stock->founded();
        break;
    case currency:
        return stock->currency();
        break;
    case employees:
        return stock->employees();
        break;
    case industries:
        return stock->industries();
        break;
    case industry:
        return stock->industry();
        break;
    case symbols:
        //return stock->symbols();
        break;
    default:
        break;
    }
    return QVariant();
}



Q_INVOKABLE Stock* Stocks::get(quint32 index) const
{
    if (index  >= m_stocks.size())
        return nullptr;
    //auto de = conversations_[index];
    return m_stocks[index];
}

void Stocks::clear()
{
    beginResetModel();
    m_stocks.clear();
    qDeleteAll(m_stocks);
    endResetModel();

    // patientMap_.clear();
    // studyMap_.clear();
    //serieMap_.clear();
}

Q_INVOKABLE bool Stocks::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    while (count--) delete m_stocks.takeAt(row);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> Stocks::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[id] = "id";
    roles[name] = "name";
    roles[country] = "country";
    roles[symbol] = "symbol";
    roles[currency] = "currency";
    roles[founded] = "founded";
    roles[employees] = "employees";
    roles[industries] = "industries";
    roles[industry] = "industry";
    roles[symbols] = "symbols";
    return roles;
}

QDateTime Stocks::computedatetime(QString date, QString time)
{
    QDate sdate(std::stoi(date.toStdString().substr(0, 4)), std::stoi(date.toStdString().substr(4, 2)), std::stoi(date.toStdString().substr(6, 2)));
    QTime stime(std::stoi(time.toStdString().substr(0, 2)), std::stoi(date.toStdString().substr(2, 2)));

    return QDateTime(sdate, stime);
}


QDateTime Stocks::computedatetime(QString datetime)
{
    auto str = datetime.toStdString();
    QDate sdate(std::stoi(str.substr(0, 4)), std::stoi(str.substr(4, 2)), std::stoi(str.substr(6, 2)));
    QTime stime(std::stoi(str.substr(8, 2)), std::stoi(str.substr(10, 2)));
    return QDateTime(sdate, stime);
}
