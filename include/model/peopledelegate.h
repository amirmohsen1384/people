#ifndef PEOPLEDELEGATE_H
#define PEOPLEDELEGATE_H

#include <QStyledItemDelegate>

class PeopleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
protected:
    virtual void RenderPhoto(QPainter *painter, const QImage &image);
public:
    PeopleDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PEOPLEDELEGATE_H
