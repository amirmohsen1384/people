#include "include/camera/photographer.h"
#include "ui_photographer.h"
#include <QCloseEvent>

void Photographer::closeEvent(QCloseEvent *event) {
    if(this->IsActive()) {
        this->Stop();
    }
    this->setResult(QDialog::Rejected);
    event->accept();
}
void Photographer::showEvent(QShowEvent *event) {
    if(!this->IsActive()) {
        this->Start();
    }
    event->accept();
}

void Photographer::Initialize() {
    session.setCamera(&camera);
    session.setImageCapture(&capture);
    session.setVideoOutput(ui->cameraView);

    settings.SetCamera(&camera);
    settings.setFixedSize(settings.size());
}

void Photographer::MakeConnection() {
    connect(&capture, &QImageCapture::imageCaptured, this, [&](int id, const QImage &preview) {
        Q_UNUSED(id)
        emit ImageCaptured(preview);
    });
    connect(this, &Photographer::CurrentDeviceChanged, this, [&](const QCameraDevice &device) {
        Q_UNUSED(device)
        if(camera.isAvailable()) {
            camera.start();
        }
    });
    connect(ui->optionsButton, &QPushButton::clicked, this, [&]() {
        if(!settings.isVisible()) {
            settings.setVisible(true);
        }
    });
    connect(this, &Photographer::AvailableDevicesChanged, this, [&]() {
        if(GetAvailableDevices().isEmpty()) {
            SetCurrentDevice(devices.defaultVideoInput());
        }
    });
    connect(&devices, &QMediaDevices::videoInputsChanged, this, &Photographer::AvailableDevicesChanged);
    connect(&capture, &QImageCapture::readyForCaptureChanged, this, &Photographer::UpdateController);
    connect(&camera, &QCamera::cameraDeviceChanged, this, &Photographer::UpdateController);
    connect(ui->captureButton, &QPushButton::clicked, &capture, &QImageCapture::capture);
    connect(&camera, &QCamera::activeChanged, this, &Photographer::UpdateController);
    connect(&camera, &QCamera::activeChanged, this, &Photographer::ActiveChanged);
    connect(this, &Photographer::ImageCaptured, this, &QDialog::accept);
}

void Photographer::UpdateController() {
    ui->optionsButton->setEnabled(camera.isAvailable());
    ui->captureButton->setEnabled(capture.isReadyForCapture());
}
Photographer::Photographer(QWidget *parent) : QDialog(parent), ui(new Ui::Photographer) {
    // Setup the user interface
    ui->setupUi(this);

    // Connect required signals to slots
    MakeConnection();

    // Initialize the camera device
    Initialize();
    UpdateController();
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
