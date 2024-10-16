#include "include/model/peoplemodel.h"

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
    case Qt::DisplayRole: {
        return person.GetFullName();
    }
    case Qt::UserRole: {
        return person;
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
bool PeopleModel::insertRows(int row, int count, const QModelIndex &parent) {
    if(parent.isValid()) {
        return false;
    }
    beginInsertRows(parent, row, row + count - 1);
    container.reserve(container.size() + count);
    for(auto i = 1; i <= count; ++i) {
        container.insert(row, Person());
    }
    endInsertRows();
}
bool PeopleModel::removeRows(int row, int count, const QModelIndex &parent) {
    if(parent.isValid()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    container.remove(row, count);
    container.squeeze();
    endRemoveRows();
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
