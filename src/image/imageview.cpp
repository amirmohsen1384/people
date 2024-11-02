#include "include/image/imageview.h"

ImageView::ImageView(QWidget *parent) : QLabel(parent) {
    this->SetImage(QImage());
    this->setScaledContents(true);
    this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}
ImageView::ImageView(const QImage &image, QWidget *parent) : ImageView(parent) {
    this->SetImage(image);
}
QImage ImageView::GetImage() const {
    const QImage &image = this->pixmap().toImage();
    return image == GetEmptyImage() ? QImage() : image;
}
QImage ImageView::GetEmptyImage() const {
    return QImage(":/images/default.png");
}
void ImageView::SetImage(const QImage &image) {
    if(!image.isNull()) {
        this->setPixmap(QPixmap::fromImage(image));

    } else {
        this->setPixmap(GetEmptyImage());

    }
    emit ImageChanged(GetImage());
}
