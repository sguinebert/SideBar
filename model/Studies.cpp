#include "Studies.h"

Studies::Studies(QObject *parent) : QAbstractListModel(parent), severalPatient_(0)
{
}

Studies::~Studies()
{
}

void Studies::addStudy(Study* study, QString uuid)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    studies_ << study;
    endInsertRows();
    studyMap_.emplace(uuid, study);
}
void Studies::encode(QString& data)
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

int Studies::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return studies_.count();
}

QVariant Studies::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= studies_.count())
        return QVariant();

    const Study* study = studies_[index.row()];
    if (role == NameRole)
        return study->name();
    else if (role == UuidRole)
        return study->uuid();
    else if (role == pid)
        return study->pid();
    else if (role == datetime)
        return study->datetime();
    //else if (role == UuidRole)
    //    return volume->uuid();
    else if (role == series)
        return study->series();
    return QVariant();
}



Q_INVOKABLE Study* Studies::get(quint32 index) const
{
    if (index  >= studies_.size())
        return nullptr;
    //auto de = conversations_[index];
    return studies_[index];
}

void Studies::clear()
{
    beginResetModel();
    studies_.clear();
    qDeleteAll(studies_);
    endResetModel();

    patientMap_.clear();
    studyMap_.clear();
    //serieMap_.clear();
}

Q_INVOKABLE bool Studies::removeRows(int row, int count, const QModelIndex& parent) 
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    while (count--) delete studies_.takeAt(row);
    endRemoveRows();
    return true;
}


QHash<int, QByteArray> Studies::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[pid] = "pid";
    roles[datetime] = "datetime";
    roles[NameRole] = "username";
    roles[UuidRole] = "uuid";
    roles[StudyDescription] = "studyDescription";
    roles[series] = "series";
    return roles;
}

QDateTime Studies::computedatetime(QString date, QString time)
{
    QDate sdate(std::stoi(date.toStdString().substr(0, 4)), std::stoi(date.toStdString().substr(4, 2)), std::stoi(date.toStdString().substr(6, 2)));
    QTime stime(std::stoi(time.toStdString().substr(0, 2)), std::stoi(date.toStdString().substr(2, 2)));

    return QDateTime(sdate, stime);
}


QDateTime Studies::computedatetime(QString datetime)
{
    auto str = datetime.toStdString();
    QDate sdate(std::stoi(str.substr(0, 4)), std::stoi(str.substr(4, 2)), std::stoi(str.substr(6, 2)));
    QTime stime(std::stoi(str.substr(8, 2)), std::stoi(str.substr(10, 2)));
    return QDateTime(sdate, stime);
}
