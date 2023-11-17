#pragma once

#include <QObject>
#include <QAbstractListModel>

#include "model/Study.h"

class Studies : public QAbstractListModel
{
	Q_OBJECT

public:
	enum StudiesRoles {
		UuidRole = Qt::UserRole + 1,
		pid,
		datetime,
		NameRole,
		StudyDescription,
		StudyNumber,
        series,
	};
	Studies(QObject* parent = 0);
	~Studies();


//	void addSerie(Volume* volume, QString useruuid, QString studyuuid, QString serieuuid, QString studyDescription, QString report);
//	void addSerie(Volume* volume, QString studyDescription, QString nip, QString useruuid, QString studyuuid, QString serieuuid, QString date, QString time);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


	Q_INVOKABLE Study* get(quint32 index) const;

	void clear();
	Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_OVERRIDE;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
	void addStudy(Study* study, QString uuid);
	void encode(QString& data);
private:
	QList<Study*> studies_;
	int severalPatient_;
	std::map<QString, int> patientMap_;
	std::map<QString, Study*> studyMap_;
    //std::map<QString, Volume*> serieMap_;

	QDateTime computedatetime(QString date, QString time);
	QDateTime computedatetime(QString datetime);

};
