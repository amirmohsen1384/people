#ifndef CAMERASETTINGS_H
#define CAMERASETTINGS_H

#include <QWidget>
#include <QCamera>
#include <QMediaDevices>

namespace Ui {
class CameraSettings;
}

class CameraSettings : public QWidget
{
    Q_OBJECT
    QMediaDevices media;
    QCamera *camera = nullptr;
    Ui::CameraSettings *ui = nullptr;
public:
    explicit CameraSettings(QCamera *camera, QWidget *parent = nullptr);
    explicit CameraSettings(QWidget *parent = nullptr);
    ~CameraSettings();
    QCamera* GetCamera();

public slots:
    void updateDevices();

public slots:
    void SetCamera(QCamera *value);

signals:
    void CameraChanged();
};

#endif // CAMERASETTINGS_H
