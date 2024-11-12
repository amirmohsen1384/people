#include "include/camera/photographer.h"
#include "ui_photographer.h"
#include <QShowEvent>

void Photographer::showEvent(QShowEvent *event) {
    this->Start();
    event->accept();
}

void Photographer::Initialize() {
    session.setCamera(&camera);
    ui->settings->SetCamera(&camera);
    session.setImageCapture(&capture);
    session.setVideoOutput(ui->cameraView);
}

void Photographer::DeviceConnection() {
    connect(this, &Photographer::CurrentDeviceChanged, this, [&](const QCameraDevice &device) {
        Q_UNUSED(device)
        if(camera.isAvailable()) {
            camera.start();
        }
    });
    connect(&devices, &QMediaDevices::videoInputsChanged, this, &Photographer::AvailableDevicesChanged);
    connect(&camera, &QCamera::cameraDeviceChanged, this, &Photographer::UpdateController);
    connect(this, &Photographer::AvailableDevicesChanged, this, [&]() {
        if(!GetAvailableDevices().isEmpty()) {
            SetCurrentDevice(devices.defaultVideoInput());

        } else {
            this->SetActive(false);

        }
    });
}
void Photographer::CaptureConnection() {
    connect(&capture, &QImageCapture::imageCaptured, this, [&](int id, const QImage &preview) {
        Q_UNUSED(id)
        emit ImageCaptured(preview);
    });
    connect(&capture, &QImageCapture::readyForCaptureChanged, this, &Photographer::UpdateController);
    connect(ui->captureButton, &QPushButton::clicked, &capture, &QImageCapture::capture);
    connect(this, &Photographer::ImageCaptured, this, &QDialog::accept);
}
void Photographer::MakeConnection() {
    DeviceConnection();
    CaptureConnection();
    connect(this, &QDialog::rejected, this, &Photographer::Stop);
    connect(&camera, &QCamera::activeChanged, this, &Photographer::ActiveChanged);
    connect(&camera, &QCamera::activeChanged, this, &Photographer::UpdateController);
    connect(ui->optionsButton, &QPushButton::toggled, ui->settings, &CameraSettings::setVisible);
}

void Photographer::UpdateController() {
    ui->settings->setVisible(false);
    ui->optionsButton->setChecked(false);
    ui->optionsButton->setEnabled(camera.isAvailable());
    ui->captureButton->setEnabled(capture.isReadyForCapture());
}

Photographer::Photographer(QWidget *parent) : QDialog(parent), ui(new Ui::Photographer) {
    ui->setupUi(this);
    UpdateController();
    MakeConnection();
    Initialize();
}
Photographer::Photographer(const QCameraDevice &device, QWidget *parent) : Photographer(parent) {
    SetCurrentDevice(device);
}

QCameraDevice Photographer::GetCurrentDevice() const {
    return camera.cameraDevice();
}

CameraList Photographer::GetAvailableDevices() const {
    return devices.videoInputs();
}

bool Photographer::IsActive() const {
    return camera.isActive();
}

void Photographer::SetCurrentDevice(const QCameraDevice &device) {
    camera.setCameraDevice(device);
    emit CurrentDeviceChanged(device);
}

void Photographer::SetActive(bool active) {
    camera.setActive(active);
}

void Photographer::Start() {
    if(camera.isAvailable() && !camera.isActive()) {
        camera.start();
    }
}

void Photographer::Stop() {
    if(camera.isAvailable() && camera.isActive()) {
        camera.stop();
    }
}

Photographer::~Photographer() {
    delete ui;
}
