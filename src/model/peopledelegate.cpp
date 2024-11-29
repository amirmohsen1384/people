#include "include/model/peopledelegate.h"
#include "include/data/person.h"
#include <QLinearGradient>
#include <QMarginsF>
#include <QPainter>

void PeopleDelegate::RenderPhoto(QPainter *painter, const QModelIndex &index, bool selected) const {
    // Obtain information from the model index
    const QImage image = qvariant_cast<QImage>(index.data(Qt::DecorationRole));

    // Save the current pen
    const QPen init = painter->pen();

    // Translate to the position
    painter->translate(QPoint(margins.left(), margins.top()));

    // Get the image rectangle
    const QRect &rectangle = image.rect();

    // Draw the image onto the view
    painter->save();
    painter->setClipRegion(QRegion(rectangle, QRegion::Ellipse));
    painter->drawImage(QPoint(0, 0), image);
    painter->restore();

    // Draw a gradient border around the image
    QLinearGradient gradient;
    gradient.setCoordinateMode(QGradient::ObjectMode);

    gradient.setStart(QPointF(0.5, 0));
    gradient.setFinalStop(QPointF(0.5, 1));

    gradient.setColorAt(0, Qt::magenta);
    gradient.setColorAt(0.7, Qt::blue);

    painter->setPen(QPen(gradient, 4));
    painter->drawEllipse(rectangle);

    // Restore the pen to the initial one
    painter->setPen(init);

    // Render the relevant icon if the item was selected
    if(selected) {
        const QImage &icon = QImage(":/icons/accept.ico");
        QPointF position = rectangle.bottomRight();
        position -= QPoint(icon.width(), icon.height());
        painter->drawImage(position, icon);
    }

    // Translate to the next point
    painter->translate(QPoint(image.rect().width() + margins.right(), 0));
}

void PeopleDelegate::RenderName(QPainter *painter, const QModelIndex &index) const {
// Construct the font which will be used when rendering the name
#ifdef Q_OS_WIN
    const QFont &font = QFont("Segoe UI Light", 18);
#endif
#ifdef Q_OS_LINUX
    const QFont &font = QFont("Ubuntu", 18);
#endif
    // Save the initial font
    const QFont &initial = painter->font();

    // Obtain the required information
    const QString &name = index.data(Qt::DisplayRole).toString();

    // Calculate the bounding rect of the name
    QFontMetricsF metrics(font);
    const QRectF &rectangle = metrics.boundingRect(name);

    // Translate to the position
    painter->translate(QPoint(margins.left(), margins.top()));

    // Render the name onto the view
    painter->setFont(font);
    painter->drawText(QPoint(0, rectangle.height()), name);

    // Reset the font
    painter->setFont(initial);

    // Translate to the next point
    painter->translate(QPoint(0, rectangle.height() + margins.bottom()));
}

void PeopleDelegate::RenderAge(QPainter *painter, const QModelIndex &index) const {
// Construct the font which will be used when rendering the age
#ifdef Q_OS_WIN
    const QFont &font = QFont("Segoe UI Light", 10);
#endif
#ifdef Q_OS_LINUX
    const QFont &font = QFont("Ubuntu Light", 10);
#endif
    // Save the initial font
    const QFont &initial = painter->font();

    // Construct the output
    const QString &output = QString("%1 year(s) old").arg(index.data(Person::AgeRole).toUInt());

    // Calculate the bounding rect of the age
    QFontMetricsF metrics(font);
    const QRectF &rectangle = metrics.boundingRect(output);

    // Render the age onto the view
    painter->setFont(font);
    painter->drawText(QPoint(0, rectangle.height()), output);

    // Reset the font
    painter->setFont(initial);

    // Translate to the next point
    painter->translate(QPoint(0, rectangle.height() + margins.bottom()));
}

QSize PeopleDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED(index)
    QSize result = QSize();
    QSize imageSize = qvariant_cast<QImage>(index.data(Qt::DecorationRole)).size();
    result.setHeight(imageSize.height() + margins.top() + margins.bottom());
    result.setWidth(600);
    return result;
}

void PeopleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // Paint the whole item with a relevant color if selected
    if(option.state.testFlag(QStyle::State_Selected)) {
        painter->fillRect(option.rect, QColor(240, 240, 240));
    }

    if(option.state.testFlag(QStyle::State_MouseOver)) {
        // Configure the font
#ifdef Q_OS_WINDOWS
        QFont font = QFont("Segoe UI", 9);
#endif
#ifdef Q_OS_LINUX
        QFont font = QFont("Ubuntu", 9);
#endif
        font.setUnderline(true);

        // Print a relevant text if selected
        const QString &help = "Double-click for more information";

        // Calculate the position
        QFontMetricsF metrics(font);
        const QRectF &region = metrics.boundingRect(help);

        QPoint position = option.rect.bottomRight();
        position -= QPoint(region.width(), region.height());
        position -= QPoint(margins.right(), margins.bottom());

        // Render the text
        QFont initialFont = painter->font();
        QPen initialPen = painter->pen();

        painter->setFont(font);
        painter->setPen(QPen(Qt::darkBlue));
        painter->drawText(position, help);

        painter->setFont(initialFont);
        painter->setPen(initialPen);
    }

    // Save the current state of the painter
    painter->save();

    // Turn on anti-aliasing mode
    painter->setRenderHint(QPainter::Antialiasing);

    // Translate to the beginning point
    QPoint point = option.rect.topLeft();
    painter->translate(point);

    // Render the photo
    RenderPhoto(painter, index, option.state.testFlag(QStyle::State_Selected));

    // Render the person's name
    RenderName(painter, index);

    // Render the person's age
    RenderAge(painter, index);
    painter->restore();
}
