#include "TableModelProxy.h"
#include <QtDebug>
#include <QtQml>

TableModelProxy::TableModelProxy(QObject *parent) :
    QSortFilterProxyModel(parent), m_complete(false), search_(false), m_sortColumn(0)
{
    connect(this, &QSortFilterProxyModel::rowsInserted, this, &TableModelProxy::countChanged);
    connect(this, &QSortFilterProxyModel::rowsRemoved, this, &TableModelProxy::countChanged);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setDynamicSortFilter(true);
    sort(0, Qt::AscendingOrder);

}

int TableModelProxy::count() const
{
    return rowCount();
}

int TableModelProxy::length() const
{
    return columnCount();
}

void TableModelProxy::setSource(TableModel *source)
{
    m_source = source;
    m_headers = m_source->headerproxy();
    setSourceModel(source);

    //connect(this, &QSortFilterProxyModel::dynamicSortFilterChanged, m_headers, &TableModelProxy::invalidate);
}

QByteArray TableModelProxy::sortRole() const
{
    return m_sortRole;
}

void TableModelProxy::setSortRole(const QByteArray &role)
{
    if (m_sortRole != role) {
        m_sortRole = role;
        if (m_complete)
            QSortFilterProxyModel::setSortRole(roleKey(role));
    }
}

int TableModelProxy::sortColumn() const
{
    return m_sortColumn;
}

void TableModelProxy::setSortColumn(const int column)
{
    if (m_sortColumn != column) {
        m_sortColumn = column;
        emit sortColumnChanged();
        sortOrder_ = Qt::SortOrder::AscendingOrder;
        setSortOrder(Qt::SortOrder::AscendingOrder);
    }
    else {
        if (sortOrder_ == Qt::SortOrder::AscendingOrder)
            sortOrder_ = Qt::SortOrder::DescendingOrder;
        else
            sortOrder_ = Qt::SortOrder::AscendingOrder;
        setSortOrder(sortOrder_);
    }
}

void TableModelProxy::setSortOrder(Qt::SortOrder order)
{
    QSortFilterProxyModel::setSortRole(m_source->role(m_sortColumn));
    QSortFilterProxyModel::sort(m_sortColumn, order);
}

QByteArray TableModelProxy::filterRole() const
{
    return m_filterRole;
}

void TableModelProxy::setFilterRole(const QByteArray &role)
{
    if (m_filterRole != role) {
        m_filterRole = role;
        if (m_complete)
            QSortFilterProxyModel::setFilterRole(roleKey(role));
    }
}



void TableModelProxy::selectRow(int row, bool shift, bool ctr)
{
    int oldUp = selectedRowUp_;
    int oldDown = selectedRowDown_;
    int ccount = columnCount();

    if (row < selectedRowUp_)
        selectedRowUp_ = row;
    if (row > selectedRowDown_)
        selectedRowDown_ = row;

    if (shift) {
        m_source->clearSelection();

        oldUp = row > baserow_? baserow_ : row;
        oldDown = row < baserow_? baserow_ : row;

        for(int i(0); i < oldDown - oldUp + 1; i++) {
            auto proxyindex = index(oldUp + i, 0);
            auto sourceindex = mapToSource(proxyindex);
            m_source->emplaceSelection(sourceindex.row());
        }
    }
    else if (ctr) {
        auto proxyindex = index(row, 0);
        auto sourceindex = mapToSource(proxyindex);
        m_source->emplaceSelection(sourceindex.row());

        emit dataChanged(index(row, 0), index(row, ccount - 1));
        return;
    }
    else {
        m_source->clearSelection();
        auto proxyindex = index(row, 0);
        auto sourceindex = mapToSource(proxyindex);
        m_source->emplaceSelection(sourceindex.row());
        QModelIndex topLeft2 = index(oldUp, 0);
        QModelIndex bottomRight2 = index(oldDown, ccount - 1);
        emit dataChanged(topLeft2, bottomRight2);

        selectedRowUp_ = row;
        selectedRowDown_ = row;
        baserow_ = row;
    }

    QModelIndex topLeft = index(selectedRowUp_, 0);
    QModelIndex bottomRight = index(selectedRowDown_, ccount - 1);
    emit dataChanged(topLeft, bottomRight);
}

Q_INVOKABLE void TableModelProxy::setFilters() //need to determine if the filters ensemble is restricted or opened (if opened : need new ws-sql request)
{
    //m_source->setFilters()

//    for (unsigned i(0); i < filters_.size(); i++) {
//        if (strFilters_[i].isEmpty())
//            filters_[i] = QRegularExpression();
//        else
//            filters_[i] = QRegularExpression("\\b(" + strFilters_[i] + ")",  static_cast<QRegularExpression::PatternOption>(filterSyntax()));
//    }
    m_source->query();

    //setFilterString("a");
    {
        QJsonObject obj;
        obj["query"] = "studies";
        obj["name"] = m_source->filter(TableModel::PatientName);
        obj["pid"] = m_source->filter(TableModel::PatientID);
        obj["datetime"] = m_source->filter(TableModel::Datetime);
        obj["description"] = m_source->filter(TableModel::StudyDescription);
        emit newRequest(obj);
    }

     //qDebug() << "setFilters()";
     invalidateFilter();
}

Q_INVOKABLE int TableModelProxy::checktype(int column)
{
    auto headertype = m_source->type(column);
    return headertype;
//    qDebug() << "headertype : " << column << " - " << headertype;
}

void TableModelProxy::headerclick(int column)
{
    setSortColumn(column);
}

QJSValue TableModelProxy::get(int idx) const
{
    QJSEngine *engine = qmlEngine(this);
    QJSValue value = engine->newObject();
    if (idx >= 0 && idx < count()) {
        QHash<int, QByteArray> roles = roleNames();
        for (auto it = roles.cbegin(), end = roles.cend(); it != end; ++it)
            value.setProperty(QString::fromUtf8(it.value()), data(index(idx, 0), it.key()).toString());
    }
    return value;
}

void TableModelProxy::classBegin()
{
}

void TableModelProxy::componentComplete()
{
    m_complete = true;
    if (!m_sortRole.isEmpty())
        QSortFilterProxyModel::setSortRole(roleKey(m_sortRole));
    if (!m_filterRole.isEmpty())
        QSortFilterProxyModel::setFilterRole(roleKey(m_filterRole));
}


int TableModelProxy::roleKey(const QByteArray &role) const
{
    return roleNames().key(role, -1);
}

QHash<int, QByteArray> TableModelProxy::roleNames() const
{
    if (QAbstractItemModel *source = sourceModel())
        return source->roleNames();
    return QHash<int, QByteArray>();
}

QString unaccent(const QString s)
{
    QString output(s.normalized(QString::NormalizationForm_D));
    return output.replace(QRegularExpression("[^a-zA-Z\\s]"), "");
}

bool TableModelProxy::filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const
{
    //qDebug() << "filterAcceptsColumn : " << sourceColumn << " - " << m_source->visible(sourceColumn);
    return m_source->visible(sourceColumn);
}

bool TableModelProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    //qDebug() << "filterrow";
    QRegularExpression rx = filterRegularExpression();
    if (!rx.isValid())
        return true;

    //return true;
    bool accepted(true);
    QAbstractItemModel *model = sourceModel();
    if (filterRole().isEmpty()) {

        QHash<int, QByteArray> roles = roleNames();
        for (auto it = roles.cbegin(), end = roles.cend(); it != end; ++it) {
            //int i = roleKey(it.value());
            QModelIndex sourceIndex = model->index(sourceRow, 0, sourceParent);

            switch(it.key()) {
            case TableModel::StudyRoles::Datetime:
            {
                auto datetime = qvariant_cast<QDateTime>(model->data(sourceIndex, it.key()));
                if(!datetimeInRange(datetime))
                    accepted = false;
            }
                break;
            case TableModel::StudyRoles::PatientBirthDate:
            {
                auto date = qvariant_cast<QDate>(model->data(sourceIndex, it.key()));
                if(!dateInRange(date))
                    accepted = false;
            }
                break;
            case TableModel::StudyRoles::AccessionNumber:
            case TableModel::StudyRoles::BodyPartExamined:
            case TableModel::StudyRoles::InstitutionName:
            case TableModel::StudyRoles::Manufacturer:
            case TableModel::StudyRoles::Modality:
            case TableModel::StudyRoles::PatientName:
            case TableModel::StudyRoles::PatientSex:
            case TableModel::StudyRoles::PatientID:
            case TableModel::StudyRoles::StudyDescription:
            case TableModel::StudyRoles::PerformedProcedureStepDescription:
            case TableModel::StudyRoles::NameOfPhysiciansReadingStudy:
            case TableModel::StudyRoles::RequestedProcedureDescription:
            case TableModel::StudyRoles::PerformingPhysicianName:
            case TableModel::StudyRoles::ReferringPhysicianName:
            case TableModel::StudyRoles::StationName:
            {
                QString key = model->data(sourceIndex, it.key()).toString();
                auto filter = m_source->regex(it.key());
                if (filter.isValid()) {
                    //qDebug() << "filters : " << filter << " - " << key ;
                    if (!filter.match(key).hasMatch())
                        accepted = false;
                }
            }
                break;

            default:
                break;
            }
        }
        return accepted;
    }
    QModelIndex sourceIndex = model->index(sourceRow, 0, sourceParent);
    if (!sourceIndex.isValid())
        return true;
    QString key = model->data(sourceIndex, roleKey(filterRole())).toString();
    return key.contains(rx);
}
