#ifndef CAMERASETTINGS_H
#define CAMERASETTINGS_H

#include <QWidget>
#include <QMediaDevices>

namespace Ui {
class CameraSettings;
}

class CameraSettings : public QWidget
{
    Q_OBJECT
    QMediaDevices devices;
    QPointer<QCamera> camera;
    Ui::CameraSettings *ui = nullptr;

private:
    void MakeConnection();
    void DeviceConnection();
    void WhiteBalanceConnection();
    void ExposureConnection();
    void FlashConnection();

private slots:
    void UpdateWhiteBalance();
    void UpdateExposure();
    void UpdateDevices();
    void UpdateOptions();
    void UpdateFlash();

public:
    explicit CameraSettings(QCamera *value, QWidget *parent = nullptr);
    explicit CameraSettings(QWidget *parent = nullptr);
    QCamera* GetCamera();

public slots:
    void SetCamera(QCamera* value);

signals:
    void CameraChanged(QCamera *value);
};

#endif // CAMERASETTINGS_H
