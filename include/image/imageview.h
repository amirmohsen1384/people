#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QImage>

class ImageView : public QWidget
{
    Q_OBJECT
    QImage image;

protected:
    void paintEvent(QPaintEvent *event);

public:
    ImageView(QWidget *parent = nullptr);
    ImageView(const QImage &image, QWidget *parent = nullptr);

    QImage GetEmptyImage() const;
    QImage GetImage() const;

public slots:
    void SetImage(const QImage &image);

signals:
    void ImageChanged(const QImage &image);
};

#endif // IMAGEVIEW_H
