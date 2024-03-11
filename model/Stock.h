#pragma once

#include <QObject>
#include <QMetaType>
#include <QQmlComponent>
#include <QDate>
#include <QDateTime>
#include <QJsonArray>


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
    //
    Q_PROPERTY(QString employees READ employees WRITE setEmployees NOTIFY employeesChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)

    Q_PROPERTY(QJsonArray symbols READ symbols NOTIFY symbolsChanged)

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
    //OHLCV
    Q_PROPERTY(QDateTime datetime READ datetime CONSTANT)
    Q_PROPERTY(double open READ open CONSTANT)
    Q_PROPERTY(double high READ high CONSTANT)
    Q_PROPERTY(double low READ low CONSTANT)
    Q_PROPERTY(double close READ close CONSTANT)
    Q_PROPERTY(qint64 volume READ volume CONSTANT)
    Q_PROPERTY(QJsonArray indices READ indices CONSTANT)
    // Q_PROPERTY(QString nameOfPhysiciansReadingStudy READ nameOfPhysiciansReadingStudy CONSTANT)
    // Q_PROPERTY(QString performedProcedureStepDescription READ performedProcedureStepDescription CONSTANT)
    // Q_PROPERTY(QString referringPhysicianName READ referringPhysicianName CONSTANT)


    QML_ELEMENT

public:
    Stock(QObject *parent = 0);
    Stock(QJsonObject json, QObject *parent = 0);
    Stock(QString& id,
          QString& name,
          QString& country,
          QString& symbol,
          QString& currency,
          QString& industry,
          QJsonArray& indices,
          QJsonArray& symbols,
          QObject *parent = 0);
    Stock(const QString& id,
          const QString& name,
          const QString& symbol,
          const QString& currency,
          QDateTime& datetime,
          double openf,
          double highf,
          double lowf,
          double closef,
          qint64 volumef,
          QObject *parent = 0);
    virtual ~Stock() { }

    QJsonArray symbols() const { return symbols_; };

    QString id() const { return id_; }
    QDate founded() const { return founded_; }

    double open() const { return open_; }
    double high() const { return high_; }
    double low() const { return low_; }
    double close() const { return close_; }
    qint64 volume() const { return volume_; }

    QString security_type() const { return security_type_; }
    QString company() const { return company_; }
    QString city() const { return city_; }
    QString industry() const { return industry_; }
    QString ib_name() const { return ib_name_; }
    QJsonArray indices() const { return indices_; }
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
//	Q_INVOKABLE Volume* getSerie(quint32 index)
signals:
    void idChanged();
    void countryChanged();
    void symbolChanged();
    void currencyChanged();
    void industriesChanged();
    void employeesChanged();
	void datetimeChanged();
    void symbolsChanged();
    void selectedChanged();
    void nameChanged();

private:
    QString id_;
    QString symbol_, currency_;
    QString name_, country_, patientID_;
    QStringList industries_;
    QString employees_;
	QDateTime datetime_;
    QJsonArray symbols_;
    QJsonArray indices_;
	bool separator_;
    bool selected_ = false;

    //QString sex_;
    QDate founded_;

    double open_, high_, low_, close_;
    qint64 volume_;

    QString studyID_,
    studyInstanceUID_,
    accessionNumber_,
    modality_,
        security_type_,
        company_,
        city_,
        industry_,
        ib_name_,
    performingPhysicianName_,
    nameOfPhysiciansReadingStudy_,
    performedProcedureStepDescription_,
    referringPhysicianName_;
};

Q_DECLARE_METATYPE(Stock);
