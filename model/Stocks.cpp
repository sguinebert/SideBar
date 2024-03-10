#include "Stocks.h"

Stocks::Stocks(QObject *parent) : QAbstractListModel(parent)//, severalPatient_(0)
{
}

Stocks::~Stocks()
{
}

void Stocks::addStock(Stock* stock/*, QString uuid*/)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    stocks_ << stock;
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
    return stocks_.count();
}

QVariant Stocks::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= stocks_.count())
        return QVariant();

    const Stock* stock = stocks_[index.row()];

    switch (role) {
    case id:

        break;
    case name:
        return stock->name();
        break;
    case country:

        break;
    case symbol:

        break;
    case founded:

        break;
    case currency:

        break;
    case employees:

        break;
    case industries:

        break;
    case symbols:

        break;
    default:
        break;
    }
    return QVariant();
}



Q_INVOKABLE Stock* Stocks::get(quint32 index) const
{
    if (index  >= stocks_.size())
        return nullptr;
    //auto de = conversations_[index];
    return stocks_[index];
}

void Stocks::clear()
{
    beginResetModel();
    stocks_.clear();
    qDeleteAll(stocks_);
    endResetModel();

    // patientMap_.clear();
    // studyMap_.clear();
    //serieMap_.clear();
}

Q_INVOKABLE bool Stocks::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    while (count--) delete stocks_.takeAt(row);
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
