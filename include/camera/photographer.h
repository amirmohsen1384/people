#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include <QDialog>
#include <QCamera>
#include <QMediaDevices>
#include <QImageCapture>
#include "camerasettings.h"
#include <QMediaCaptureSession>

namespace Ui {
class Photographer;
}

class Photographer : public QDialog
{
    Q_OBJECT
    QCamera camera;
    QMediaDevices devices;
    QImageCapture capture;
    CameraSettings settings;
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
    bool IsActive() const;

public slots:
    void SetCurrentDevice(const QCameraDevice &device);
    void SetActive(bool active);
    void Start();
    void Stop();

signals:
    void CurrentDeviceChanged(const QCameraDevice &camera);
    void ImageCaptured(const QImage &image);
    void ActiveChanged(bool active);
    void AvaliableDevicesChanged();

};

#endif // PHOTOGRAPHER_H
