#pragma once

#include <QObject>
#include <QMetaType>
#include <QQmlComponent>
#include <QDate>
#include <QDateTime>

class Stock : public QObject
{
    Q_OBJECT // Macro for signals and slots
	Q_PROPERTY(QString pid READ pid NOTIFY pidChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
	Q_PROPERTY(QString userid READ userid WRITE setUserid NOTIFY useridChanged)
	Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged)
	Q_PROPERTY(QStringList sdescription READ sdescription NOTIFY sdescriptionChanged)
	Q_PROPERTY(QDateTime datetime READ datetime WRITE setDatetime NOTIFY datetimeChanged)
	Q_PROPERTY(QString report READ report WRITE setReport NOTIFY reportChanged)
	Q_PROPERTY(bool separator READ separator WRITE setSeparator NOTIFY separatorChanged)
		Q_PROPERTY(QVariantList series READ series NOTIFY seriesChanged)

    Q_PROPERTY(QString sex READ sex CONSTANT)
    Q_PROPERTY(QDate birthDate READ birthDate CONSTANT)
    Q_PROPERTY(QString studyID READ studyID CONSTANT)
    Q_PROPERTY(QString studyInstanceUID READ studyInstanceUID CONSTANT)
    Q_PROPERTY(QString accessionNumber READ accessionNumber CONSTANT)
    Q_PROPERTY(QString modality READ modality CONSTANT)
    Q_PROPERTY(QString institutionName READ institutionName CONSTANT)
    Q_PROPERTY(QString manufacturer READ manufacturer CONSTANT)
    Q_PROPERTY(QString stationName READ stationName CONSTANT)
    Q_PROPERTY(QString requestedProcedureDescription READ requestedProcedureDescription CONSTANT)
    Q_PROPERTY(QString bodyPartExamined READ bodyPartExamined CONSTANT)
    Q_PROPERTY(QString performingPhysicianName READ performingPhysicianName CONSTANT)
    Q_PROPERTY(QString nameOfPhysiciansReadingStudy READ nameOfPhysiciansReadingStudy CONSTANT)
    Q_PROPERTY(QString performedProcedureStepDescription READ performedProcedureStepDescription CONSTANT)
    Q_PROPERTY(QString referringPhysicianName READ referringPhysicianName CONSTANT)


    QML_ELEMENT

public:
    Stock(QObject *parent = 0);
    Stock(QJsonObject json, QObject *parent = 0);
    Stock(int pid, QString name, QString description, QString user_id, QString uuid, QDateTime datetime, QObject *parent = 0, QString report = QString());
    virtual ~Stock() { }

	QVariantList series() const { return series_; };

	QString pid() const { return pid_; }

    QString sex() const { return sex_; }
    QDate birthDate() const { return birthDate_; }
    QString studyID() const { return studyID_; }
    QString studyInstanceUID() const { return studyInstanceUID_; }
    QString accessionNumber() const { return accessionNumber_; }
    QString modality() const { return modality_; }
    QString institutionName() const { return institutionName_; }
    QString manufacturer() const { return manufacturer_; }
    QString stationName() const { return stationName_; }
    QString requestedProcedureDescription() const { return requestedProcedureDescription_; }
    QString bodyPartExamined() const { return bodyPartExamined_; }
    QString performingPhysicianName() const { return performingPhysicianName_; }
    QString nameOfPhysiciansReadingStudy() const { return nameOfPhysiciansReadingStudy_; }
    QString performedProcedureStepDescription() const { return performedProcedureStepDescription_; }
    QString referringPhysicianName() const { return referringPhysicianName_; }


	QString name() const { return name_; }
	void setName(const QString& name);

	QString description() const { return description_; }
	void setDescription(const QString& description);

	QString userid() const { return user_id_; }
	void setUserid(const QString& userid); 

	QString uuid() const { return uuid_; }
	void setUuid(const QString& uuid);

	QString report() const { return report_; }
	void setReport(const QString& report);

	QStringList sdescription() const { return sdescription_; }
	void appendSDescription(const QString& sdescription, int numSerie);

	QDateTime datetime() const { return datetime_; }
	void setDatetime(const QDateTime& datetime);

	bool separator() const { return separator_; }
    void setSeparator(const bool separator);

    bool selected() const { return selected_; }
    void setSelected(const bool selected);

//	Q_INVOKABLE void appendSerie(Volume *volume);
//	Q_INVOKABLE Volume* getSerie(quint32 index);

signals:
	void pidChanged();
	void nameChanged();
	void descriptionChanged();
	void useridChanged();
	void uuidChanged();
	void sdescriptionChanged();
	void datetimeChanged();
	void seriesChanged();
	void separatorChanged();
	void reportChanged();

private:
	QString pid_;
	QString user_id_, uuid_;
	QString name_, description_, patientID_;
	QStringList sdescription_;
	QString report_;
	QDateTime datetime_;
	QVariantList series_;
	bool separator_;
    bool selected_ = false;

    QString sex_;
    QDate birthDate_;
    QString studyID_,
    studyInstanceUID_,
    accessionNumber_,
    modality_,
    institutionName_,
    manufacturer_,
    stationName_,
    requestedProcedureDescription_,
    bodyPartExamined_,
    performingPhysicianName_,
    nameOfPhysiciansReadingStudy_,
    performedProcedureStepDescription_,
    referringPhysicianName_;
};

Q_DECLARE_METATYPE(Stock);
