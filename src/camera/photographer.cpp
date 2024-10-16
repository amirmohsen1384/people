#include "include/camera/photographer.h"
#include "ui_photographer.h"

void Photographer::Initialize() {
    session.setCamera(&camera);
    session.setImageCapture(&capture);
    session.setVideoOutput(ui->cameraView);
}
void Photographer::MakeConnection() {
    connect(ui->captureButton, &QPushButton::clicked, &capture, &QImageCapture::capture);
    connect(&capture, &QImageCapture::imageCaptured, [this](int id, const QImage &preview) {
        Q_UNUSED(id)
        emit ImageCaptured(preview);
    });
    connect(this, &Photographer::CurrentDeviceChanged, [this](const QCameraDevice &device) {
        Q_UNUSED(device)
        if(camera.isAvailable()) {
            camera.start();
        }
    });
}
Photographer::Photographer(QWidget *parent) : QDialog(parent), ui(new Ui::Photographer) {
    ui->setupUi(this);
    MakeConnection();
    Initialize();
    if(camera.isAvailable()) {
        camera.start();
    }
}
Photographer::Photographer(const QCameraDevice &device, QWidget *parent) : Photographer(parent) {
    SetCurrentDevice(device);
}
QCameraDevice Photographer::GetCurrentDevice() const {
    return camera.cameraDevice();
}
void Photographer::SetCurrentDevice(const QCameraDevice &device) {
    camera.setCameraDevice(device);
    emit CurrentDeviceChanged(device);
}
Photographer::~Photographer() {
    delete ui;
}
