#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>

class ImageView : public QLabel
{
    Q_OBJECT
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
