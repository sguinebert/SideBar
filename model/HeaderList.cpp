#include "HeaderList.h"

HeaderList::HeaderList(QObject* parent) : QAbstractListModel(parent)
{
}

void HeaderList::addHeader(const QString &title, const QString &key, int sourceIndex, int position, int width, Header::Type type, bool visibility)
{
    auto header = new Header(title, key, position, width, type, visibility, this);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_headers.append(header);
    endInsertRows();

//    if(m_headers.size() <= sourceIndex) {
    //        m_headers.resize(sourceIndex, header);
//        beginInsertRows(QModelIndex(), rowCount(), rowCount());
//        m_headers.append(header);
//        endInsertRows();
//    }
//    else {
//        //beginInsertRows(QModelIndex(), sourceIndex, sourceIndex);
//        m_headers[sourceIndex] = header;
//        //endInsertRows();
//    }

    if(header->visibility()) {
        count_++;

        //qDebug() <<title << " - " << key << " - " << sourceIndex << " - " << position;

        bool inserted(false);

        for(int i(0); i < m_columnOrder.size(); ++i) {

            if(position < m_headers[m_columnOrder[i]]->position()) {
                m_columnOrder.insert(i, sourceIndex);
                inserted = true;
                break;
            }

        }
        if(!inserted)
            m_columnOrder.push_back(sourceIndex);
    }



//    if(m_columnOrder.size() <= sourceIndex)
//        m_columnOrder.resize(sourceIndex + 1, sourceIndex);

//    m_columnOrder[sourceIndex] = position;

    if(title == "Procedure Description") {

        qDebug() << m_columnOrder;
        for(auto head : m_headers) {
            qDebug() << head->title() << " - " << head->position();
        }
    }

}

int HeaderList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.size();
    //return count_;
}

QVariant HeaderList::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_headers.size())
        return QVariant();

    const Header* header = m_headers[index.row()];

    switch (role) {
    case Type:
        return header->type();
    case Title:
        return header->title();
    case Width:
        return header->width();
    case Visibility:
        return header->visibility();
    case Position:
        return header->position();
    case Filter:
        return header->filter();
    case RegexFilter:
        return header->regexfilter();
    default:
        break;
    }

    //qDebug() << "HeaderList::data() - Invalid role";

    return QVariant();
}

Header *HeaderList::get(quint32 index) const
{
    if (index  >= m_headers.size())
        return nullptr;
    return m_headers[index];
}

bool HeaderList::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    while (count--) delete m_headers.takeAt(row);
    endRemoveRows();
    return true;
}

void HeaderList::clear()
{
    beginResetModel();
    m_headers.clear();
    qDeleteAll(m_headers);
    endResetModel();
}

QHash<int, QByteArray> HeaderList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Type] = "type";
    roles[Title] = "title";
    roles[Width] = "width";
    roles[Visibility] = "visibility";
    roles[Position] = "position";
    roles[Filter] = "filter";
//    roles[StudyDescription] = "studyDescription";
//    roles[series] = "series";
    return roles;
}
