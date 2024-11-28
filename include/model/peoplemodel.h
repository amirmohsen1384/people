#ifndef PEOPLEMODEL_H
#define PEOPLEMODEL_H

#include "include/data/person.h"
#include <QAbstractListModel>

class PeopleModel : public QAbstractListModel
{
    Q_OBJECT
    PersonList container;
private:
    static QString ShortenFullName(const QString &value);
    static QString DisplayLastModification(const QDateTime &value);

public:
    explicit PeopleModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    explicit PeopleModel(const PersonList &value, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QList<QModelIndex> Find(const QString &keyword) const;
    Person Obtain(const QModelIndex &index) const;
    const PersonList& GetContainer() const;

public slots:
    void SetContainer(const PersonList &value);

    void Insert(int row, const PersonList &data);
    void Insert(int row, const Person &data);

    void Append(const Person &data);
    void Append(const PersonList &data);

    void Remove(QModelIndexList &indices);
    void Remove(QModelIndex &index);

    void Clear();

    bool Modify(const QModelIndex &index, const Person &data);
};

#endif // PEOPLEMODEL_H
