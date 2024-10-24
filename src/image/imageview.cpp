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
    return (this->pixmap().toImage() == QImage(":/images/default.png")) ? QImage() : this->pixmap();
}
void ImageView::SetImage(const QImage &image) {
    if(!image.isNull()) {
        this->setPixmap(QPixmap::fromImage(image));

    } else {
        this->setPixmap(QPixmap(":/images/default.png"));

    }
    emit ImageChanged(GetImage());
}
