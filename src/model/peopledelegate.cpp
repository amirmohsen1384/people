#include "include/model/peopledelegate.h"
#include "include/data/person.h"
#include <QLinearGradient>
#include <QMarginsF>
#include <QPainter>

void PeopleDelegate::RenderPhoto(QPainter *painter, const QImage &image) {
    painter->save();

    painter->setClipRegion(QRegion(image.rect(), QRegion::Ellipse));
    painter->drawImage(QPoint(0, 0), image);

    painter->restore();

    QLinearGradient gradient;
    gradient.setCoordinateMode(QGradient::ObjectMode);

    gradient.setStart(QPointF(0.5, 0));
    gradient.setFinalStop(QPointF(0.5, 1));

    gradient.setColorAt(0, Qt::blue);
    gradient.setColorAt(0.5, Qt::red);

    painter->setPen(QPen(gradient, 4));

    painter->drawEllipse(image.rect());
}

QSize PeopleDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return (600, 120);
}

void PeopleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // Define a margin for the contents
    const QMarginsF margins(10, 10, 30, 10);

    // Save the current state of the painter
    painter->save();

    // Render the person's photo
    const QImage &picture = qvariant_cast<QImage>(index.data(Qt::DecorationRole));
    painter->translate(margins.left(), margins.top());
    RenderPhoto(painter, picture);

    // Move the painter foward by the width of the picture
    painter->translate(picture.width() + margins.right(), 0);

    // Render the person's name
    const QString &name = index.data(Qt::DisplayRole).toString();
    painter->translate(margins.left(), 0);
    painter->drawText(QPoint(0, 0), name);

    painter->restore();
}
