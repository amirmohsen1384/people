#include "include/image/imageview.h"
#include <QPaintEvent>
#include <QPainter>

void ImageView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QImage image = QImage();
    const QRect &region = event->rect();

    if(image.isNull()) {
        image = GetEmptyImage();

    } else {
        image = this->image;

    }

    QPainter painter(this);
    painter.drawImage(image.rect(), image, region);
}

ImageView::ImageView(QWidget *parent) : QWidget(parent) {}
ImageView::ImageView(const QImage &image, QWidget *parent) : ImageView(parent) {
    this->SetImage(image);
}

QImage ImageView::GetImage() const {
    return image;
}
QImage ImageView::GetEmptyImage() const {
    return QImage(":/images/default.png");
}
void ImageView::SetImage(const QImage &image) {
    this->image = image;
    emit ImageChanged(GetImage());
}
