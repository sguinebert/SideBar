#include "TableModel.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>



QString header2key(TableModel::StudyRoles role) {
    switch (role) {
    case TableModel::PatientName:
        return "PatientName";
    case TableModel::PatientID:
        return "PatientId"; // Corrected to match the key in headtemplate
    case TableModel::Datetime:
        return "Datetime";
    case TableModel::StudyDescription:
        return "StudyDescription";
    case TableModel::PatientSex:
        return "PatientSex";
    case TableModel::PatientBirthDate:
        return "PatientBirthDate";
    case TableModel::Modality:
        return "Modality";
    case TableModel::StationName:
        return "StationName";
    case TableModel::InstitutionName:
        return "InstitutionName";
    case TableModel::AccessionNumber:
        return "AccessionNumber";
    case TableModel::PerformingPhysicianName:
        return "PerformingPhysicianName";
    case TableModel::NameOfPhysiciansReadingStudy:
        return "NameOfPhysiciansReadingStudy";
    case TableModel::PerformedProcedureStepDescription:
        return "PerformedProcedureStepDescription";
    case TableModel::Manufacturer:
        return "Manufacturer";
    case TableModel::BodyPartExamined:
        return "BodyPartExamined";
    case TableModel::RequestedProcedureDescription:
        return "RequestedProcedureDescription";
    default:
        break;
    }
    return "";
}


TableModel::TableModel(QObject* parent) : QAbstractTableModel(parent)
{
    //cwidths_ = { 200, 200, 200, 100 };

    m_headers = new HeaderList(this);

    m_headerproxy = new HeaderListProxy(m_headers);
    m_headerproxy->setSourceModel(m_headers);

    m_filters = new FiltersList(this);

    QJsonObject headtemplate;
    //headtemplate["AET"] = "caveo";
    headtemplate["PatientName"] = QJsonArray({ PatientName, 0, 200, 0, true});
    headtemplate["PatientSex"] = QJsonArray({PatientSex, 4, 200, 0, true});
    headtemplate["PatientBirthDate"] = QJsonArray({PatientBirthDate, 5, 200, 1, true});
    headtemplate["PatientId"] = QJsonArray({ PatientID, 1, 200, 0, true});
    headtemplate["Datetime"] = QJsonArray({ Datetime, 2, 200, 2, true});
    headtemplate["Modality"] = QJsonArray({Modality, 6, 200, 0, true});
    headtemplate["StudyDescription"] = QJsonArray({StudyDescription, 3, 200, 0, true});
    headtemplate["StationName"] = QJsonArray({StationName, 7, 200, 0, true});

    headtemplate["InstitutionName"] = QJsonArray({InstitutionName, 8, 200, 0, true});
    headtemplate["AccessionNumber"] = QJsonArray({AccessionNumber, 9, 200, 0, true});

    headtemplate["PerformingPhysicianName"] = QJsonArray({PerformingPhysicianName, 10, 200, 0, true});
    headtemplate["NameOfPhysiciansReadingStudy"] = QJsonArray({NameOfPhysiciansReadingStudy, 11, 200, 0, true});
    headtemplate["PerformedProcedureStepDescription"] = QJsonArray({PerformedProcedureStepDescription, 12, 200, 0, true});

    headtemplate["Manufacturer"] = QJsonArray({Manufacturer, 13, 200, 0, true});
    headtemplate["BodyPartExamined"] = QJsonArray({BodyPartExamined, 14, 200, 0, true});
    headtemplate["RequestedProcedureDescription"] = QJsonArray({RequestedProcedureDescription, 15, 200, 0, true});

//    headtemplate["StudyID"] = QJsonArray({StudyID, 16, 200, 0, true});
//    headtemplate["StudyInstanceUID"] = QJsonArray({StudyInstanceUID, 17, 200, 0, true});
//    QJsonObject({
//    {"Position", 0},
//    {"Visibility", true},
//    {"Type", 0},
//    });
    int hsize = ReferringPhysicianName - PatientName;

    for(int i = 0; i < hsize; i++) {
        auto role = (TableModel::StudyRoles)(PatientName + i);
        auto key = header2key(role);
        const auto& value = headtemplate.value(key).toArray();
        auto title = header2string(role);

        if(!value.isEmpty())
            m_headers->addHeader(title, //title
                                 key,
                                 i, //original index
                                 value[1].toInt(), //position
                                 value[2].toInt(), //width
                                 (Header::Type)value[3].toInt(), //type
                                 value[4].toBool()); //visibility
        else
            m_headers->addHeader(title, //title
                                 key,
                                 i, //original index
                                 -1, //position
                                 200, //width
                                 Header::Type::Text, //type
                                 false); //visibility

    }

    QJsonObject obj;
    obj["test"] = "test";
    m_filters->addFilter("Caveo", "filtre 1", obj);
    m_filters->addFilter("Caveo", "filtre 2", obj);
    m_filters->addFilter("Caveo", "filtre 2", obj);

    m_currentLocale = QLocale::system();

    auto study = new Study(21313212, "test","description", "user_id", "5896468465156341354", QDateTime::currentDateTime(), 0);
    addStudy(study, "joijioj");
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            return m_headerproxy->data(m_headerproxy->index(section, 0), HeaderList::Title);
            //return m_headers->data(m_headers->index(section), HeaderList::Title);
        else
            return QString("ver-%1").arg(section);
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return studies_.size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_headers->rowCount();
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= studies_.size())
        return QVariant();

    const Study* study = studies_[index.row()];
    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column() + PatientName)
        {
        case PatientName:
            return study->name();
            break;
        case PatientID:
            return study->pid();
            break;
        case Datetime:
            return  study->datetime().toString(m_currentLocale.dateTimeFormat(QLocale::ShortFormat));
            break;
        case StudyDescription:
            return study->description();
            break;
        case PatientSex:
            return study->sex();
            break;
        case PatientBirthDate:
            return study->birthDate().toString(m_currentLocale.dateFormat(QLocale::ShortFormat));
            break;
        case StudyInstanceUID:
            return study->studyInstanceUID();
            break;
        case AccessionNumber:
            return study->accessionNumber();
            break;
        case Modality:
            return study->modality();
            break;
        case InstitutionName:
            return study->institutionName();
            break;
        case Manufacturer:
            return study->manufacturer();
            break;
        case StationName:
            return study->stationName();
            break;
        case BodyPartExamined:
            return study->bodyPartExamined();
            break;
        case RequestedProcedureDescription:
            return study->requestedProcedureDescription();
            break;
        case PerformingPhysicianName:
            return study->performingPhysicianName();
            break;
        case PerformedProcedureStepDescription:
            return study->performedProcedureStepDescription();
            break;
        case ReferringPhysicianName:
            return study->referringPhysicianName();
            break;
        default:
            break;
        }

        break;
    case PatientName:
        return study->name();
        break;
    case PatientID:
        return study->pid();
        break;
    case Datetime:
        return  study->datetime();
        break;
    case StudyDescription:
        return study->description();
        break;
    case PatientSex:
        return study->sex();
        break;
    case PatientBirthDate:
        return study->birthDate();
        break;
    case StudyInstanceUID:
        return study->studyInstanceUID();
        break;
    case AccessionNumber:
        return study->accessionNumber();
        break;
    case Modality:
        return study->modality();
        break;
    case InstitutionName:
        return study->institutionName();
        break;
    case Manufacturer:
        return study->manufacturer();
        break;
    case StationName:
        return study->stationName();
        break;
    case BodyPartExamined:
        return study->bodyPartExamined();
        break;
    case RequestedProcedureDescription:
        return study->requestedProcedureDescription();
        break;
    case PerformingPhysicianName:
        return study->performingPhysicianName();
        break;
    case PerformedProcedureStepDescription:
        return study->performedProcedureStepDescription();
        break;
    case ReferringPhysicianName:
        return study->referringPhysicianName();
        break;

    case Qt::DecorationRole:
        if (std::find(selectedRows_.begin(), selectedRows_.end(), index.row()) != selectedRows_.end()) //(selectedRowUp_ <= index.row() && index.row() <= selectedRowDown_) ||
            return "#80DEEA";
        return index.row() % 2 == 0 ? "white" : "#EEEEEE";
        break;

    case Qt::EditRole:
        break;
    case Qt::ToolTipRole:
        break;
    case Qt::StatusTipRole:
        break;
    case Qt::WhatsThisRole:
        break;
    case Qt::FontRole:
        break;
    case Qt::TextAlignmentRole:
        break;
    case Qt::BackgroundRole:
        break;
    case Qt::ForegroundRole:
        break;
    case Qt::CheckStateRole:
        break;
    case Qt::AccessibleTextRole:
        break;
    case Qt::AccessibleDescriptionRole:
        break;
    case Qt::SizeHintRole:
        break;
    case Qt::InitialSortOrderRole:
        break;
    // ... include other cases as needed
    case Qt::DisplayPropertyRole:
        break;
    case Qt::DecorationPropertyRole:
        break;
    case Qt::ToolTipPropertyRole:
        break;
    case Qt::StatusTipPropertyRole:
        break;
    case Qt::WhatsThisPropertyRole:
        break;
    default:
        break;
    }


//    if (index.row() < studies_.size()) {
//        const Study* study = studies_[index.row()];
//        if ((role == Qt::DisplayRole && index.column() == m_columnOrder[Name]) || role == Name) //index.column() == 0
//            return study->name();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[Pid]) || role == Pid) //index.column() == 1
//            return study->pid();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[Datetime]))
//            return  study->datetime().toString(m_currentLocale.dateTimeFormat(QLocale::ShortFormat));
//        else if(role == Datetime)
//            return  study->datetime();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[StudyDescription]) || role == StudyDescription)
//            return study->description();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[PatientSex]) || role == PatientSex)
//            return study->sex();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[PatientBirthDate]))
//            return study->birthDate().toString(m_currentLocale.dateFormat(QLocale::ShortFormat));
//        else if (role == PatientBirthDate)
//            return  study->birthDate();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[StudyInstanceUID]) || role == StudyInstanceUID)
//            return study->studyInstanceUID();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[AccessionNumber]) || role == AccessionNumber)
//            return study->accessionNumber();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[Modality]) || role == Modality)
//            return study->modality();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[InstitutionName]) || role == InstitutionName)
//            return study->institutionName();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[Manufacturer]) || role == Manufacturer)
//            return study->manufacturer();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[StationName]) || role == StationName)
//            return study->stationName();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[BodyPartExamined]) || role == BodyPartExamined)
//            return study->bodyPartExamined();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[RequestedProcedureDescription]) || role == RequestedProcedureDescription)
//            return study->requestedProcedureDescription();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[PerformingPhysicianName]) || role == PerformingPhysicianName)
//            return study->performingPhysicianName();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[NameOfPhysiciansReadingStudy]) || role == NameOfPhysiciansReadingStudy)
//            return study->nameOfPhysiciansReadingStudy();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[PerformedProcedureStepDescription]) || role == PerformedProcedureStepDescription)
//            return study->performedProcedureStepDescription();
//        else if ((role == Qt::DisplayRole && index.column() == m_columnOrder[ReferringPhysicianName]) || role == ReferringPhysicianName)
//            return study->referringPhysicianName();
//        else if (role == Qt::DecorationRole && index.row() >= 0 && index.row() < rowCount() && index.column() >= 0 && index.column() < columnCount()) {
//            if (std::find(selectedRows_.begin(), selectedRows_.end(), index.row()) != selectedRows_.end()) //(selectedRowUp_ <= index.row() && index.row() <= selectedRowDown_) ||
//                return "#80DEEA";
//            return index.row() % 2 == 0 ? "white" : "#EEEEEE";
//        }
//    }
    return QVariant();
}
void findKey(const QString& query, const QJsonValue& value, std::vector<QString>& keys, std::vector<QJsonObject>& vec, const QString& oldkey) {
    if (value.isObject()) {
        const QJsonObject obj = value.toObject();
        if (obj.contains(query)&&obj.value(query).toInt()==1) {
            vec.push_back(obj["data"].toObject());           // return 'early' if object contains key
            keys.push_back(oldkey);
        }

        foreach(const QString& key, obj.keys()) {
            QJsonValue value = obj.value(key);
            findKey(query, value, keys, vec, key);  // call itself, forwarding a value
            //            if (!recurse.isNull()&&recurse.toInt()==1){
            //                vec.push_back(obj);            // value found, return 'early'
        }
    } else if (value.isArray()) {
//        for (const auto& value : value.toArray()) {
//            QJsonValue recurse = findKey(key, value);
//            if (!recurse.isNull()&&recurse.toInt()==1)
//                return value;
//        }
    }

    //return QJsonValue();          // base case: a null value
}
void TableModel::addFilter(QJsonObject json)
{
    auto section = json["section"].toString();
    auto filters = json["filter"].toObject();

    std::vector<QString> keys;
    std::vector<QJsonObject> obj;
    findKey("type", filters, keys, obj, "");

//    for(const auto &vv : obj){
//        QString strFromObj = QJsonDocument(vv).toJson(QJsonDocument::Compact).toStdString().c_str();
//        qDebug() << "ddd : " << strFromObj;

//    }
//    for(auto & cc :keys )
//        qDebug() << "ddd : " << cc;
//    for(const auto &it : json){
//        if(it.isObject()){
//        }
//    }
    for(unsigned i(0); i < keys.size(); i++){
        m_filters->addFilter(section, keys[i], obj[i]);
    }



}
void TableModel::addStudy(Study* study, std::string uuid)
{
    if (uuids_.find(uuid) == uuids_.end()) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        studies_ << study;
        endInsertRows();

        uuids_.emplace(uuid);
    }
    //studyMap_.emplace(uuid, study);
}
void TableModel::addStudy(QJsonObject json)
{
    auto study = new Study(json, this);
    addStudy(study, json["uuid"].toString().toStdString());
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[Qt::DecorationRole] = "style";
    roles[PatientID] = "pid";
    roles[Datetime] = "datetime";
    roles[PatientName] = "name";
    roles[Uuid] = "uuid";
    roles[StudyDescription] = "studyDescription";
    roles[PatientSex] = "patientSex";

    roles[PatientBirthDate] = "patientBirthDate";
    roles[StudyID] = "studyID";
    roles[StudyInstanceUID] = "studyInstanceUID";
    roles[AccessionNumber] = "accessionNumber";
    roles[Modality] = "modality";
    roles[InstitutionName] = "institutionName";
    roles[Manufacturer] = "manufacturer";
    roles[StationName] = "stationName";
    roles[BodyPartExamined] = "bodyPartExamined";
    roles[PerformingPhysicianName] = "performingPhysicianName";
    roles[NameOfPhysiciansReadingStudy] = "nameOfPhysiciansReadingStudy";
    roles[PerformedProcedureStepDescription] = "performedProcedureStepDescription";
    roles[ReferringPhysicianName] = "referringPhysicianName";

    roles[Series] = "series";
    return roles;
}

Q_INVOKABLE void TableModel::loadstudy(int index)
{
    emit loadStudy(studies_[index]);
}

void TableModel::selectFilter(int index)
{
    auto filter = m_filters->get(index);

    std::cout << "test filter " << std::endl;

    if(filter) {
        qDebug() << "filter : " << filter->title();
        m_headers->setFilters(filter->filters());
        m_headerproxy->invalidate();
    }
}
