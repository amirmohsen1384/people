#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include <QDialog>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>

namespace Ui {
class Photographer;
}

class Photographer : public QDialog
{
    Q_OBJECT
    QCamera camera;
    QImageCapture capture;
    QMediaCaptureSession session;
    Ui::Photographer *ui = nullptr;

private:
    void Initialize();
    void MakeConnection();
    void UpdateController();
public:
    ~Photographer();
    explicit Photographer(QWidget *parent = nullptr);
    explicit Photographer(const QCameraDevice &device, QWidget *parent = nullptr);

    QCameraDevice GetCurrentDevice() const;

public slots:
    void SetCurrentDevice(const QCameraDevice &device);

signals:
    void CurrentDeviceChanged(const QCameraDevice &camera);
    void ImageCaptured(const QImage &image);
};

#endif // PHOTOGRAPHER_H
