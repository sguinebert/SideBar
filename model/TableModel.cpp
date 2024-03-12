#include "TableModel.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>

#include "magic_enum/magic_enum.hpp"

QString header2key(TableModel::StockRoles role) {

    // switch (role) {
    // case TableModel::PatientName:
    //     return "PatientName";
    // case TableModel::PatientID:
    //     return "PatientId"; // Corrected to match the key in headtemplate
    // case TableModel::Datetime:
    //     return "Datetime";
    // case TableModel::StudyDescription:
    //     return "StudyDescription";
    // case TableModel::PatientSex:
    //     return "PatientSex";
    // case TableModel::PatientBirthDate:
    //     return "PatientBirthDate";
    // case TableModel::Modality:
    //     return "Modality";
    // case TableModel::StationName:
    //     return "StationName";
    // case TableModel::InstitutionName:
    //     return "InstitutionName";
    // case TableModel::AccessionNumber:
    //     return "AccessionNumber";
    // case TableModel::PerformingPhysicianName:
    //     return "PerformingPhysicianName";
    // case TableModel::NameOfPhysiciansReadingStudy:
    //     return "NameOfPhysiciansReadingStudy";
    // case TableModel::PerformedProcedureStepDescription:
    //     return "PerformedProcedureStepDescription";
    // case TableModel::Manufacturer:
    //     return "Manufacturer";
    // case TableModel::BodyPartExamined:
    //     return "BodyPartExamined";
    // case TableModel::RequestedProcedureDescription:
    //     return "RequestedProcedureDescription";
    // default:
    //     break;
    // }
    return "";
}


TableModel::TableModel(DataProvider* dataprovider, QObject* parent) :
    QAbstractTableModel(parent),
    m_dataprovider(dataprovider)
{
    //cwidths_ = { 200, 200, 200, 100 };

    m_headers = new HeaderList(this);

    m_headerproxy = new HeaderListProxy(m_headers);
    m_headerproxy->setSourceModel(m_headers);

    m_filters = new FiltersList(this);


    QJsonObject headtemplate;
    if(m_dataprovider) {
        headtemplate["name"] = QJsonArray({ name, 0, 200, Header::Text, true});
        headtemplate["symbol"] = QJsonArray({ symbol, 1, 200, Header::Text, true});
        headtemplate["datetime"] = QJsonArray({ datetime, 2, 200, Header::DateTime, true});
        headtemplate["open"] = QJsonArray({ open, 3, 200, Header::Text, true});
        headtemplate["high"] = QJsonArray({ high, 4, 200, Header::Text, true});
        headtemplate["low"] = QJsonArray({ low, 5, 200, Header::Text, true});
        headtemplate["close"] = QJsonArray({ close, 6, 200, Header::Text, true});
        headtemplate["volume"] = QJsonArray({ volume, 7, 200, Header::Text, true});
        // headtemplate["StudyDescription"] = QJsonArray({StudyDescription, 3, 200, 0, true});
        // headtemplate["StationName"] = QJsonArray({StationName, 7, 200, 0, true});

    }
    connect(m_dataprovider, &DataProvider::dataReceived, this, &TableModel::addStock);

    //headtemplate["AET"] = "caveo";


    // headtemplate["InstitutionName"] = QJsonArray({InstitutionName, 8, 200, 0, true});
    // headtemplate["AccessionNumber"] = QJsonArray({AccessionNumber, 9, 200, 0, true});

    // headtemplate["PerformingPhysicianName"] = QJsonArray({PerformingPhysicianName, 10, 200, 0, true});
    // headtemplate["NameOfPhysiciansReadingStudy"] = QJsonArray({NameOfPhysiciansReadingStudy, 11, 200, 0, true});
    // headtemplate["PerformedProcedureStepDescription"] = QJsonArray({PerformedProcedureStepDescription, 12, 200, 0, true});

    // headtemplate["Manufacturer"] = QJsonArray({Manufacturer, 13, 200, 0, true});
    // headtemplate["BodyPartExamined"] = QJsonArray({BodyPartExamined, 14, 200, 0, true});
    // headtemplate["RequestedProcedureDescription"] = QJsonArray({RequestedProcedureDescription, 15, 200, 0, true});

//    headtemplate["StudyID"] = QJsonArray({StudyID, 16, 200, 0, true});
//    headtemplate["StudyInstanceUID"] = QJsonArray({StudyInstanceUID, 17, 200, 0, true});
//    QJsonObject({
//    {"Position", 0},
//    {"Visibility", true},
//    {"Type", 0},
//    });


    constexpr auto count = magic_enum::enum_count<StockRoles>();
    for(int i(0); i < count; i++) {
        auto cc = magic_enum::enum_name(static_cast<StockRoles>(id + i));
        QString key = QString::fromUtf8(cc.data(), cc.size());
        //auto key = names[i];

        const auto& value = headtemplate.value(key.data()).toArray();
        //auto title = header2string(role);
        auto title = key;

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

    //auto study = new Stock(21313212, "test","description", "user_id", "5896468465156341354", QDateTime::currentDateTime(), 0);
    //addStudy(study, "joijioj");
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
    return stocks_.size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_headers->rowCount();
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= stocks_.size())
        return QVariant();
    qDebug() << "role : " << role << " - " << " index : " << index.row() << " - " << index.column();
    const Stock* stock = stocks_[index.row()];
    switch (role)
    {
        // name,
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
        // datetime,
        // open,
        // high,
        // low,
        // close,
        // volume,
    case Qt::DisplayRole:
        switch (index.column() + id) {
        case StockRoles::id:
            return stock->id();
            break;
        case StockRoles::name:
            return stock->name();
            break;
        case StockRoles::ib_name:
            return stock->ib_name();
            break;
        case StockRoles::state:
            return stock->country();
            break;
        case StockRoles::city:
            return stock->city();
            break;
        case StockRoles::contract_id:
            //return stock->contract_id();
            break;
        case StockRoles::ib_conid:
            break;
        case StockRoles::symbol:
            return stock->symbol();
            break;
        case StockRoles::security_type:
            break;
        case StockRoles::currency:
            return stock->currency();
            break;
        case StockRoles::company:
            return stock->company();
            break;
        case StockRoles::industry:
            return stock->industry();
            break;
        case StockRoles::datetime:
            return stock->datetime();
            break;
        case StockRoles::open:
            return stock->open();
            break;
        case StockRoles::high:
            return stock->high();
            break;
        case StockRoles::low:
            return stock->low();
            break;
        case StockRoles::close:
            return stock->close();
            break;
        case StockRoles::volume:
            return stock->volume();
            break;
        case StockRoles::selected:
            return stock->selected();
            break;
        default:
            // Handle unknown roles
            break;
        }
        break;
    case StockRoles::id:
        return stock->id();
        break;
    case StockRoles::name:
        return stock->name();
        break;
    case StockRoles::ib_name:
        return stock->ib_name();
        break;
    case StockRoles::state:
        return stock->country();
        break;
    case StockRoles::city:
        return stock->city();
        break;
    case StockRoles::contract_id:
        //return stock->contract_id();
        break;
    case StockRoles::ib_conid:
        break;
    case StockRoles::symbol:
        return stock->symbol();
        break;
    case StockRoles::security_type:
        break;
    case StockRoles::currency:
        return stock->currency();
        break;
    case StockRoles::company:
        return stock->company();
        break;
    case StockRoles::industry:
        return stock->industry();
        break;
    case StockRoles::datetime:
        return stock->datetime();
        break;
    case StockRoles::open:
        return stock->open();
        break;
    case StockRoles::high:
        return stock->high();
        break;
    case StockRoles::low:
        return stock->low();
        break;
    case StockRoles::close:
        return stock->close();
        break;
    case StockRoles::volume:
        return stock->volume();
        break;
    case StockRoles::selected:
        return stock->selected();
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
void TableModel::addStudy(Stock* study, std::string uuid)
{
    if (uuids_.find(uuid) == uuids_.end()) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        stocks_ << study;
        endInsertRows();

        uuids_.emplace(uuid);
    }
    //studyMap_.emplace(uuid, study);
}
void TableModel::addStudy(QJsonObject json)
{
    auto study = new Stock(json, this);
    addStudy(study, json["uuid"].toString().toStdString());
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "display";
    roles[Qt::DecorationRole] = "style";
    // roles[PatientID] = "pid";
    // roles[Datetime] = "datetime";
    // roles[PatientName] = "name";
    // roles[Uuid] = "uuid";
    // roles[StudyDescription] = "studyDescription";
    // roles[PatientSex] = "patientSex";

    // roles[PatientBirthDate] = "patientBirthDate";
    // roles[StudyID] = "studyID";
    // roles[StudyInstanceUID] = "studyInstanceUID";
    // roles[AccessionNumber] = "accessionNumber";
    // roles[Modality] = "modality";
    // roles[InstitutionName] = "institutionName";
    // roles[Manufacturer] = "manufacturer";
    // roles[StationName] = "stationName";
    // roles[BodyPartExamined] = "bodyPartExamined";
    // roles[PerformingPhysicianName] = "performingPhysicianName";
    // roles[NameOfPhysiciansReadingStudy] = "nameOfPhysiciansReadingStudy";
    // roles[PerformedProcedureStepDescription] = "performedProcedureStepDescription";
    // roles[ReferringPhysicianName] = "referringPhysicianName";

    //roles[Series] = "series";
    return roles;
}

Q_INVOKABLE void TableModel::loadstudy(int index)
{
    emit loadStudy(stocks_[index]);
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
