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

    Qt::ItemFlags flags(const QModelIndex &index) const;

    const PersonList& GetContainer() const;
    void SetContainer(const PersonList &value);
};

#endif // PEOPLEMODEL_H
