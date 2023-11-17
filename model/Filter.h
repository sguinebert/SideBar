 #pragma once

#include <QObject>
#include <QString>
#include <QJsonObject>

class Filter : public QObject
{

public:
    Filter(const QString& section, const QString& title, const QJsonObject& filters, QObject *parent = nullptr);

    QString section() const { return m_section; }
    QString title() const { return m_title; }
    const QJsonObject& filters() const { return m_filters; }

private:
    QString m_section;
    QString m_title;
    QJsonObject m_filters;
};

