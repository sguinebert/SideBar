#include "Filter.h"

Filter::Filter(const QString& section, const QString& title, const QJsonObject& filters, QObject *parent) :
    QObject(parent),
    m_section(section),
    m_title(title),
    m_filters(filters)
{

}
