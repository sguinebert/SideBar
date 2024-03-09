#include "Stock.h"

#include <QJsonObject>

Stock::Stock(QObject *parent) : QObject(parent)
{
}

Stock::Stock(QJsonObject json, QObject* parent): QObject(parent), separator_(false)
{
//    for(const auto& key : json.keys()){
//        auto value = json.value(key);
//        qDebug() << "json : " << key << " - " << value;
//    }
//json :  "AccessionNumber"  -  QJsonValue(string, "S104628152")
//json :  "BodyPartExamined"  -  QJsonValue(string, "")
//json :  "InstitutionName"  -  QJsonValue(string, "HEGP")
//json :  "Manufacturer"  -  QJsonValue(string, "GE MEDICAL SYSTEMS")
//json :  "Modality"  -  QJsonValue(string, "MR")
//json :  "NameOfPhysiciansReadingStudy"  -  QJsonValue(string, "ORL")
//json :  "PatientSex"  -  QJsonValue(string, "F")
//json :  "PerformedProcedureStepDescription"  -  QJsonValue(string, "")
//json :  "PerformingPhysicianName"  -  QJsonValue(string, "")
//json :  "ReferringPhysicianName"  -  QJsonValue(string, "1.63")
//json :  "StationName"  -  QJsonValue(string, "EGPIRM2")
//json :  "bday"  -  QJsonValue(string, "07121962")
//json :  "datetime"  -  QJsonValue(string, "200720221610")
//json :  "description"  -  QJsonValue(string, "IRM ROCHER")
//json :  "modality"  -  QJsonValue(string, "MR")
//json :  "name"  -  QJsonValue(string, "SEQUEIRA^MARIE-LOUISE")
//json :  "pid"  -  QJsonValue(string, "8016285351")
//json :  "sd"  -  QJsonValue(string, "4cf1b470-756c-4537-8a4e-6470af4393b8")
//json :  "uuid"  -  QJsonValue(string, "c95a6df3-cb66-418a-9dde-8c11bf3ef2fd")

//        QString sex_, studyID_,
//        studyInstanceUID_,
//        accessionNumber_,
//        modality_,
//        institutionName_,
//        manufacturer_,
//        stationName_,
//        requestedProcedureDescription_,
//        bodyPartExamined_,
//        performingPhysicianName_,
//        nameOfPhysiciansReadingStudy_,
//        performedProcedureStepDescription_,
//        referringPhysicianName_

	patientID_ = json["pid"].toString();
	pid_ = patientID_;
	name_ = json["name"].toString(); 
	description_ = json["description"].toString(); 
	user_id_ = json["sd"].toString();
	uuid_ = json["uuid"].toString();
    modality_ = json["modality"].toString();
    sex_ = json["PatientSex"].toString();
    modality_ = json["Modality"].toString();
    stationName_ = json["StationName"].toString();
    accessionNumber_ = json["AccessionNumber"].toString();
    manufacturer_ = json["Manufacturer"].toString();
    institutionName_ = json["InstitutionName"].toString();
    performingPhysicianName_ = json["PerformingPhysicianName"].toString();
    referringPhysicianName_ = json["ReferringPhysicianName"].toString();
    performedProcedureStepDescription_ = json["PerformedProcedureStepDescription"].toString();

    auto bday = json["bday"].toString();
    birthDate_.setDate(bday.mid(4, 4).toInt(), bday.mid(2, 2).toInt(), bday.mid(0, 2).toInt());

    auto str = json["datetime"].toString();
    if (str.size() > 7) {
        datetime_.setDate(QDate(str.mid(4, 4).toInt(), str.mid(2, 2).toInt(), str.mid(0, 2).toInt()));
        datetime_.setTime(str.size() > 8 ? QTime(str.mid(8, 2).toInt(), str.mid(10, 2).toInt()) : QTime());
	}
}

Stock::Stock(int pid, QString name, QString description, QString user_id, QString uuid, QDateTime datetime, QObject* parent, QString report) :
    QObject(parent), pid_(QString::number(pid)), name_(name), user_id_(user_id), uuid_(uuid), datetime_(datetime), separator_(true), report_(report)
{
	description_ = datetime.toString("dd/MM/yyyy") + " - " + description;
}



void Stock::setName(const QString& name)
{
	if (name_ != name) {
		name_ = name;
		emit nameChanged();
	}
}

void Stock::setDescription(const QString& description)
{
	if (description_ != description) {
		description_ = description;
		emit descriptionChanged();
	}
}

void Stock::setUserid(const QString& userid)
{
	if (user_id_ != userid) {
		user_id_ = userid;
		emit useridChanged();
	}
}

void Stock::setUuid(const QString& uuid)
{
	if (uuid_ != uuid) {
		uuid_ = uuid;
		emit uuidChanged();
	}
}

void Stock::setReport(const QString& report)
{
	if (report_ != report) {
		report_ = report;
		emit reportChanged();
	}

}

void Stock::appendSDescription(const QString& sdescription, int numSerie)
{
	if (series_.size() <= numSerie) {
		sdescription_.append(sdescription);
	}
	else
		sdescription_.insert(numSerie, sdescription);
	//sdescription_.append(sdescription);
	emit sdescriptionChanged();
}

void Stock::setDatetime(const QDateTime& datetime)
{
	if (datetime_ != datetime) {
		datetime_ = datetime;
		emit datetimeChanged();
	}
}

void Stock::setSeparator(const bool separator)
{
	if (separator_ != separator) {
		separator_ = separator;
		emit separatorChanged();
    }
}

void Stock::setSelected(const bool selected)
{
    selected_ = selected;
}

//Q_INVOKABLE void Study::appendSerie(Volume* volume)
//{
//	int numSerie = volume->snum() - 1;

//    for(int i(0); i < series_.size(); i++) {
//        auto vol = qvariant_cast<Volume*>(series_[i]);
//        if(numSerie < vol->snum()) {
//            series_.insert(i, QVariant::fromValue(volume));
//            emit seriesChanged();
//            return Q_INVOKABLE void();
//        }
//    }
//    series_.append(QVariant::fromValue(volume));

////	if (series_.size() <= numSerie) {

////	}
////	else
////		series_.insert(numSerie, QVariant::fromValue(volume));
//	//series_.append(QVariant::fromValue(volume));
	
//    //appendSDescription(volume->serieDescription(), numSerie);
//	emit seriesChanged();
//	return Q_INVOKABLE void();
//}

//Q_INVOKABLE Volume* Study::getSerie(quint32 index)
//{
//	if (index >= series_.size())
//		return nullptr;
//	return qvariant_cast<Volume*>(series_[index]);
//	//return nullptr;
//}
