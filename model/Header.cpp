#include "Header.h"

Header::Header(const QString &title, const QString &key, int position, int width, Type type, bool visibility, QObject *parent) :
    QObject(parent),
    m_title(title),
    m_key(key),
    m_position(position),
    m_width(width),
    m_type(type),
    m_visibility(visibility)
{
}

void Header::setVisibility(bool visibility)
{
    if(m_visibility == visibility)
        return;

    m_visibility = visibility;
    //emit visibilityChanged();
}

void Header::setPosition(int position)
{
    if(m_position == position)
        return;

    m_position = position;
    emit positionChanged();
}

void Header::setWidth(int width)
{
    //qDebug() << "setWidth()" << width;
    if(m_width == width)
        return;

    m_width = width;
    emit widthChanged();
}

void Header::setFilter(const QString& filter)
{
    if(m_filter == filter)
        return;

    m_filter = filter;
    emit filterChanged();
}
