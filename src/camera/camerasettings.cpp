#include "include/camera/camerasettings.h"
#include "ui_camerasettings.h"

CameraSettings::CameraSettings(QWidget *parent) : QWidget(parent), ui(new Ui::CameraSettings) {
    ui->setupUi(this);
    connect(&media, &QMediaDevices::videoInputsChanged, this, &CameraSettings::updateDevices);
}
void CameraSettings::updateDevices() {
    auto webcams = this->media.videoInputs();
    if(webcams.isEmpty()) {
        ui->mainTab->setTabEnabled(USING_CAMERA, false);
        ui->mainTab->setTabText(USING_CAMERA, ui->mainTab->tabText(USING_CAMERA) + " - Not supported");
        return;
    }

    for (const QCameraDevice &single : webcams) {
        ui->deviceComboBox->addItem(single.description(), QVariant::fromValue(single));
    }
    this->mainWebcam.setCameraDevice(webcams.constFirst());

    // Enable camera device-related settings
    ui->deviceComboBox->setEnabled(true);
    ui->deviceLabel->setEnabled(true);
    ui->deviceGroup->setEnabled(true);

    // Connect the webcam to webcam viewer
    ui->webcamView->SetWebcam(&mainWebcam);
}

CameraSettings::CameraSettings(QCamera *camera, QWidget *parent) : CameraSettings(parent) {
    SetCamera(camera);
}
CameraSettings::~CameraSettings() {
    delete ui;
}

QCamera *CameraSettings::GetCamera() {
    return camera;
}
void CameraSettings::SetCamera(QCamera *value) {
    camera = value;
    emit CameraChanged();
}
