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
    connect(&capture, &QImageCapture::readyForCaptureChanged, this, &Photographer::UpdateController);
    connect(&camera, &QCamera::cameraDeviceChanged, this, &Photographer::UpdateController);
    connect(&camera, &QCamera::activeChanged, this, &Photographer::UpdateController);
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

    // Start the camera
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
