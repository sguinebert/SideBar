#pragma once

#include <QObject>
#include <QQmlComponent>
#include <QString>
#include <QRegularExpression>


class Header : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool visibility READ visibility WRITE setVisibility NOTIFY visibilityChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
//    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
//    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
//    Q_PROPERTY(QString userid READ userid WRITE setUserid NOTIFY useridChanged)
//    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged)
//    Q_PROPERTY(QStringList sdescription READ sdescription NOTIFY sdescriptionChanged)
//    Q_PROPERTY(QDateTime datetime READ datetime WRITE setDatetime NOTIFY datetimeChanged)
//    Q_PROPERTY(QString report READ report WRITE setReport NOTIFY reportChanged)
//    Q_PROPERTY(bool separator READ separator WRITE setSeparator NOTIFY separatorChanged)
//        Q_PROPERTY(QVariantList series READ series NOTIFY seriesChanged)
    QML_ELEMENT
public:
    enum Type {
      Text,
      Date,
      DateTime,
      ComboBox,
      PopupBox,
      CheckBox
    };
public:
    Header(const QString &title, const QString &key, int position, int width, Type type, bool visibility, QObject *parent = 0);

    bool visibility() const { return m_visibility; }
    QString title() const { return m_title; }
    QString filter() const { return m_filter; }
    QString key() const { return m_key; }
    int position() const { return m_position; }
    int width() const { return m_width; }
    Type type() const { return m_type; }

    void setVisibility(bool visibility);
    void setPosition(int visibility);
    void setWidth(int width);
    void setFilter(const QString& filter);

    QRegularExpression regexfilter() const {
        return m_filter.isEmpty() ? QRegularExpression() :  QRegularExpression("\\b(" + m_filter + ")", QRegularExpression::PatternOption::CaseInsensitiveOption);
    }

signals:
    void visibilityChanged();
    void positionChanged();
    void filterChanged();
    void widthChanged();

private:
    QString m_title, m_key;
    int m_position, m_width;
    Type m_type;
    bool m_visibility;
    QString m_filter;
};
