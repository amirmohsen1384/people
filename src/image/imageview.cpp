#include "include/image/imageview.h"
#include <QPaintEvent>
#include <QPainter>

void ImageView::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QImage image = this->image;
    const QRect &region = event->rect();

    if(image.isNull()) {
        image = GetEmptyImage();
    }

    QPainter painter(this);
    painter.drawImage(region, image, image.rect());
}

void ImageView::updateImage() {
    update();
}

ImageView::ImageView(QWidget *parent) : QWidget(parent) {
    connect(this, &ImageView::ImageChanged, this, &ImageView::updateImage);
}
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
    emit ImageChanged(image);
}
