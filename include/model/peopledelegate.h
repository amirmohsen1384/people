#ifndef PEOPLEDELEGATE_H
#define PEOPLEDELEGATE_H

#include <QStyledItemDelegate>

class PeopleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    const QMarginsF margins = QMarginsF(10, 10, 10, 10);

protected:
    virtual void RenderPhoto(QPainter *painter, const QModelIndex &index, bool selected = false) const;
    virtual void RenderName(QPainter *painter, const QModelIndex &index) const;
    virtual void RenderAge(QPainter *painter, const QModelIndex &index) const;

public:
    PeopleDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PEOPLEDELEGATE_H
