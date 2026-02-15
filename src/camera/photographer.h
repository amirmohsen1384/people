#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include <QDialog>
#include <QCamera>
#include <QMediaDevices>
#include <QImageCapture>
#include <QMediaCaptureSession>

namespace Ui {
class Photographer;
}

using CameraList = QList<QCameraDevice>;

class Photographer : public QDialog
{
    Q_OBJECT
    QCamera camera;
    QMediaDevices devices;
    QImageCapture capture;
    QMediaCaptureSession session;
    Ui::Photographer *ui = nullptr;

protected:
    virtual void showEvent(QShowEvent *event) override;

private:
    void Initialize();
    void MakeConnection();
    void UpdateController();
    void DeviceConnection();
    void CaptureConnection();

public:
    ~Photographer();
    explicit Photographer(QWidget *parent = nullptr);
    explicit Photographer(const QCameraDevice &device, QWidget *parent = nullptr);

    bool IsActive() const;
    QCameraDevice GetCurrentDevice() const;
    CameraList GetAvailableDevices() const;

public slots:
    void SetCurrentDevice(const QCameraDevice &device);
    void SetActive(bool active);
    void Start();
    void Stop();

signals:
    void CurrentDeviceChanged(const QCameraDevice &camera);
    void ImageCaptured(const QImage &image);
    void ActiveChanged(bool active);
    void AvailableDevicesChanged();

};



#endif // PHOTOGRAPHER_H
