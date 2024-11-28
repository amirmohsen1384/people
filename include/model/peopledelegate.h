#ifndef PEOPLEDELEGATE_H
#define PEOPLEDELEGATE_H

#include <QStyledItemDelegate>

class PeopleDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    PeopleDelegate(QObject *parent) : QStyledItemDelegate(parent) {}
};

#endif // PEOPLEDELEGATE_H
