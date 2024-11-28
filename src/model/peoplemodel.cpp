#include "include/data/differencedate.h"
#include "include/model/peoplemodel.h"
#include <algorithm>

QString PeopleModel::ShortenFullName(const QString &value) {
    const qsizetype length = 24;
    QString result = value;

    result.truncate(length);
    if(value.size() > length) {
        result.append("...");
    }

    return result;
}
QString PeopleModel::DisplayLastModification(const QDateTime &value) {
    QString output = QString("Last Modification: ");
    quint64 days = value.daysTo(QDateTime::currentDateTime());
    if(days < 7) {
        output.append(QString("%1 day(s) ago").arg(days));

    } else {
        quint64 weeks = days / 7;
        if(weeks < 4) {
            output.append(QString("%1 week(s) ago").arg(weeks));

        } else {
            quint64 months = weeks / 4;
            if(months > 3) {
                output.append(QString("A long time ago"));

            } else {
                output.append(QString("%1 month(s) ago").arg(months));

            }
        }
    }
    return output;
}

PeopleModel::PeopleModel(const PersonList &value, QObject *parent) : PeopleModel(parent) {
    SetContainer(value);
}

int PeopleModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return container.size();
}
QVariant PeopleModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const Person &person = container.at(index.row());

    switch(role) {
    case Qt::UserRole:
    case Person::PersonRole: {
        return QVariant::fromValue(person);
    }

    case Qt::DisplayRole: {
        return PeopleModel::ShortenFullName(person.GetFullName());
    }

    case Person::NameRole: {
        return person.GetFullName();
    }

    case Person::PhotoRole: {
        return person.GetPhoto();
    }

    case Qt::DecorationRole: {
        const QSize &size = QSize(96, 96);
        return person.GetPhoto().scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    case Qt::ToolTipRole: {
        return PeopleModel::DisplayLastModification(person.GetLastModification());
    }

    case Person::GenderRole: {
        return QVariant::fromValue(person.GetGender());
    }

    case Person::AgeRole: {
        return DifferenceDate::GetDifference(person.GetBirthday()).GetYear();
    }

    case Person::CreationRole: {
        return person.GetCreation();
    }

    case Person::BirthdayRole: {
        return person.GetBirthday();
    }

    case Person::FirstNameRole: {
        return person.GetFirstName();
    }

    case Person::LastNameRole: {
        return person.GetLastName();
    }

    case Person::LastModificationRole: {
        return person.GetLastModification();
    }

    default: {
        return QVariant();
    }

    }
}

bool PeopleModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || role != Qt::UserRole) {
        return false;
    }
    container.replace(index.row(), qvariant_cast<Person>(value));
    emit dataChanged(index, index, {Qt::UserRole});
    return true;
}

Qt::ItemFlags PeopleModel::flags(const QModelIndex &index) const {
    if(!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemNeverHasChildren;
}

const PersonList &PeopleModel::GetContainer() const {
    return container;
}

void PeopleModel::SetContainer(const PersonList &value) {
    beginResetModel();
    container = value;
    endResetModel();
}

void PeopleModel::Insert(int row, const PersonList &data) {
    const int first = row;
    PersonListIterator iterator(data);
    const int last = row + data.size() - 1;

    beginInsertRows(QModelIndex(), first, last);
    for(int i = first; i <= last; ++i) {
        container.insert(i, iterator.next());
    }
    endInsertRows();
}

void PeopleModel::Insert(int row, const Person &data) {
    beginInsertRows(QModelIndex(), row, row);
    container.insert(row, data);
    endInsertRows();
}

void PeopleModel::Append(const Person &data) {
    Insert(container.size(), data);
}

void PeopleModel::Append(const PersonList &data) {
    Insert(container.size(), data);
}


void PeopleModel::Remove(QModelIndexList &indices) {
    auto lambda = [&] (QModelIndex &one, QModelIndex &two) {
        return (one.row() < two.row());
    };
    std::sort(indices.begin(), indices.end(), lambda);
    for(auto iterator = indices.rbegin(); iterator != indices.rend(); ++iterator) {
        this->Remove(*iterator);
    }
}
void PeopleModel::Remove(QModelIndex &index) {
    const int row = index.row();
    beginRemoveRows(QModelIndex(), row, row);
    container.removeAt(row);
    container.squeeze();
    endRemoveRows();
}

void PeopleModel::Clear() {
    beginResetModel();
    container.clear();
    endResetModel();
}

QList<QModelIndex> PeopleModel::Find(const QString &keyword) const {
    QList<QModelIndex> occurrences;
    for(int i = 0; i < this->rowCount(); ++i) {
        const QModelIndex &index = this->index(i);
        const QString &name = this->Obtain(index).GetFullName();
        if(name.contains(keyword, Qt::CaseInsensitive)) {
            occurrences.append(index);
        }
    }
    return occurrences;
}

bool PeopleModel::Modify(const QModelIndex &index, const Person &data) {
    return this->setData(index, QVariant::fromValue(data), Qt::UserRole);
}

Person PeopleModel::Obtain(const QModelIndex &index) const {
    if(!index.isValid()) {
        return Person();
    }
    return container.at(index.row());
}
