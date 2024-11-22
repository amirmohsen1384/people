#include "include/model/peoplemodel.h"
#include <QDataStream>
#include <QSaveFile>
#include <QIODevice>
#include <algorithm>
#include <QFile>

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
    case Qt::UserRole: {
        return QVariant::fromValue(person);
    }

    case Qt::DisplayRole: {
        return person.GetFullName();
    }

    case Qt::ToolTipRole: {
        QString toolTip;
        toolTip.append("Last Modified: ");
        toolTip.append(person.GetLastModification().toString());
        return toolTip;
    }

    case Qt::DecorationRole: {
        const QSize &dimensions = QSize(128, 128);
        return person.GetPhoto().scaled(dimensions, Qt::KeepAspectRatio, Qt::SmoothTransformation);
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
