#ifndef PEOPLEMODEL_H
#define PEOPLEMODEL_H

#include "include/data/person.h"
#include <QAbstractListModel>

class PeopleModel : public QAbstractListModel
{
    Q_OBJECT
    PersonList container;

public:
    explicit PeopleModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    explicit PeopleModel(const PersonList &value, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

public:
    const PersonList& GetContainer() const;
    void SetContainer(const PersonList &value);

    void Insert(int row, const PersonList &data);
    void Insert(int row, const Person &data);

    void Append(const Person &data);
    void Append(const PersonList &data);

    void Remove(const QModelIndexList &indices);
    void Remove(const QModelIndex &index);

    void Clear();

    QList<QModelIndex> Find(const QString &keyword) const;

    bool Modify(const QModelIndex &index, const Person &data);
    Person Obtain(const QModelIndex &index) const;

    bool Load(const QString &filename);
    bool Load(const QIODevice *device);

    bool Save(const QString &filename, const QModelIndexList &indices, bool appendMode = true);
    bool Save(QIODevice *device, const QModelIndexList &indices);

    bool Save(QIODevice *device);
    bool Save(const QString &filename, bool appendMode = true);
};

#endif // PEOPLEMODEL_H
