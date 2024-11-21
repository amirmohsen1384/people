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
        return person.GetPhoto();
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
    if(parent.isValid() || count <= 0) {
        return false;
    }

    const int first = row - 1;
    row = (row <= 0) ? 1 : row;
    const int last = (row - 2) + count;

    container.reserve(container.size() + count);

    beginInsertRows(parent, first, last);
    for(auto i = first; i <= last; ++i) {
        container.insert(i, Person());
    }
    endInsertRows();

    return true;
}

bool PeopleModel::removeRows(int row, int count, const QModelIndex &parent) {
    if(parent.isValid() || count <= 0 || row < 0) {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    container.remove(row, count);
    container.squeeze();
    endRemoveRows();
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
    PersonListIterator iterator(data);
    while(iterator.hasNext()) {
        this->Insert(row, iterator.next());
    }
}

void PeopleModel::Insert(int row, const Person &data) {
    insertRow(row);
    setData(this->index(row - 1), QVariant::fromValue(data), Qt::UserRole);
}

void PeopleModel::Append(const Person &data) {
    Insert(this->rowCount(), data);
}

void PeopleModel::Append(const PersonList &data) {
    Insert(this->rowCount(), data);
}

void PeopleModel::Remove(const QModelIndexList &indices) {
    QListIterator<QModelIndex> iterator(indices);
    while(iterator.hasNext()) {
        this->Remove(iterator.next());
    }
}

void PeopleModel::Remove(const QModelIndex &index) {
    removeRow(index.row());
}

void PeopleModel::Clear() {
    beginResetModel();
    container.clear();
    endResetModel();
}

QList<QModelIndex> PeopleModel::Find(const QString &keyword) const {
    QList<QModelIndex> indices;
    for(int i = 0; i < this->rowCount(); ++i) {
        const QModelIndex &index = this->index(i);
        const QString &name = this->Obtain(index).GetFullName();
        if(name.contains(keyword, Qt::CaseInsensitive)) {
            indices.append(index);
        }
    }
    return indices;
}

bool PeopleModel::Modify(const QModelIndex &index, const Person &data) {
    return this->setData(index, data, Qt::UserRole);
}

Person PeopleModel::Obtain(const QModelIndex &index) {
    return qvariant_cast<Person>(this->data(index, Qt::UserRole));
}

#include <QFile>
#include <QIODevice>
#include <QSaveFile>
#include <QDataStream>

const quint64 magic = 0x419A202E;

bool PeopleModel::Load(const QString &filename) {
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)) {
        return false;
    }
    return this->Load(&file);
}

bool PeopleModel::Load(const QIODevice *device) {
    if(!device->isReadable()) {
        return false;
    }

    try {
        QDataStream input(device);

        // Read the magic number from the stream
        quint64 number = 0;
        input >> number;
        if(number != magic) {
            return false;
        }

        // Read the count of elements from the stream;
        quint64 count = 0;
        input >> count;

        // Read information from the stream
        PersonList information;
        information.reserve(count);

        for(quint64 i = 0; i < count; ++i) {
            Person data;
            input >> data;
            information.append(data);
        }

        this->SetContainer(information);
        return true;

    } catch(...) {
        return false;

    }
}

bool PeopleModel::Save(QIODevice *device, const QModelIndexList &indices) {
    if(!device->isWritable()) {
        return false;
    }
    try {
        QDataStream output(device);

        // I write a magic number to check if the given stream is valid when reading.
        output << magic;

        // Write the count of elements to the stream
        stream << indices.size();

        // Write the elements to the stream
        QListIterator<QModelIndex> iterator(indices);
        while(iterator.hasNext()) {
            output << Obtain(iterator.next());
        }

        return true;

    } catch(...) {
        return false;
    }
}

bool PeopleModel::Save(QIODevice *device) {
    QModelIndexList indices;
    for(int i = 0; i < rowCount(); ++i) {
        indices.append(this->index(i));
    }
    return this->Save(device, indices);
}
bool PeopleModel::Save(const QString &filename, bool appendMode) {
    QModelIndexList indices;
    for(int i = 0; i < rowCount(); ++i) {
        indices.append(this->index(i));
    }
    return this->Save(filename, indices, appendMode);
}

bool PeopleModel::Save(const QString &filename, const QModelIndexList &indices, bool appendMode) {
    QSaveFile file(filename);
    if(!file.open(appendMode ? QIODevice::Append : QIODevice::WriteOnly)) {
        return false;
    }
    return this->Save(&file, indices);
}
