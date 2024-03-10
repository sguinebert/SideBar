#pragma once

#include <QObject>
#include <QMetaType>
#include <QQmlComponent>
#include <QDate>
#include <QDateTime>
    // id = Qt::UserRole + 1,
    // Name,
    // ib_name,
    // state,
    // city,
    // contract_id,
    // ib_conid,
    // symbol,
    // security_type,
    // currency,
    // company,
    // industry,
    // selected

    // name,
    // country,
    // symbol,
    // currency,
    // founded,
    // employees,
    // industries,
    // symbols
class Stock : public QObject
{
public:
    enum Provider {
        Yahoo,
        Google
    };
    typedef std::pair<Provider, QString> apiprovider;
private:
    Q_OBJECT // Macro for signals and slots
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString symbol READ symbol WRITE setSymbol NOTIFY symbolChanged)
    Q_PROPERTY(QString currency READ currency WRITE setCurrency NOTIFY currencyChanged)
    Q_PROPERTY(QStringList industries READ industries NOTIFY industriesChanged)
    //Q_PROPERTY(QDateTime founded READ founded WRITE setFounded NOTIFY foundedChanged)
    Q_PROPERTY(QString employees READ employees WRITE setEmployees NOTIFY employeesChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
        Q_PROPERTY(QVector<apiprovider> symbols READ symbols NOTIFY symbolsChanged)

    // ib_name,
    // state,
    // city,
    // contract_id,
    // ib_conid,
    // symbol,
    // security_type,
    // currency,
    // company,
    // industry,
    // selected
    Q_PROPERTY(QString ib_name READ ib_name CONSTANT)
    Q_PROPERTY(QDate founded READ founded CONSTANT)
    Q_PROPERTY(QString city READ city CONSTANT)
    Q_PROPERTY(QString security_type READ security_type CONSTANT)
    Q_PROPERTY(QString company READ company CONSTANT)
    Q_PROPERTY(QString industry READ industry CONSTANT)
    // Q_PROPERTY(QString institutionName READ institutionName CONSTANT)
    // Q_PROPERTY(QString manufacturer READ manufacturer CONSTANT)
    // Q_PROPERTY(QString stationName READ stationName CONSTANT)
    // Q_PROPERTY(QString requestedProcedureDescription READ requestedProcedureDescription CONSTANT)
    // Q_PROPERTY(QString bodyPartExamined READ bodyPartExamined CONSTANT)
    // Q_PROPERTY(QString performingPhysicianName READ performingPhysicianName CONSTANT)
    // Q_PROPERTY(QString nameOfPhysiciansReadingStudy READ nameOfPhysiciansReadingStudy CONSTANT)
    // Q_PROPERTY(QString performedProcedureStepDescription READ performedProcedureStepDescription CONSTANT)
    // Q_PROPERTY(QString referringPhysicianName READ referringPhysicianName CONSTANT)


    QML_ELEMENT

public:
    Stock(QObject *parent = 0);
    Stock(QJsonObject json, QObject *parent = 0);
    Stock(int id, QString name, QString description, QString user_id, QString uuid, QDateTime datetime, QObject *parent = 0, QString report = QString());
    virtual ~Stock() { }

    QVector<apiprovider> symbols() const { return symbols_; };

    QString id() const { return id_; }

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

    QString country() const { return country_; }
    void setCountry(const QString& country);

    QString symbol() const { return symbol_; }
    void setSymbol(const QString& symbol);

    QString currency() const { return currency_; }
    void setCurrency(const QString& currency);

    QString employees() const { return employees_; }
    void setEmployees(const QString& employees);

    QStringList industries() const { return industries_; }
    void setIndustries(const QString& industries, int numSerie);

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
    QString id_;
    QString symbol_, currency_;
    QString name_, country_, patientID_;
    QStringList industries_;
    QString employees_;
	QDateTime datetime_;
    QVector<apiprovider> symbols_;
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
