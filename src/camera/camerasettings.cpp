#include "include/camera/camerasettings.h"
#include "ui_camerasettings.h"
#include <QCameraDevice>

CameraSettings::CameraSettings(QWidget *parent) : QWidget(parent), ui(new Ui::CameraSettings) {
    ui->setupUi(this);
    MakeConnection();
}
CameraSettings::CameraSettings(QCamera *value, QWidget *parent) : CameraSettings(parent) {
    SetCamera(value);
}

void CameraSettings::MakeConnection() {
    DeviceConnection();
}

void CameraSettings::DeviceConnection() {
    connect(&devices, &QMediaDevices::videoInputsChanged, this, &CameraSettings::UpdateDevices);
    connect(ui->deviceComboBox, &QComboBox::currentIndexChanged, this, [&](int index) {
        Q_UNUSED(index)
        camera->setCameraDevice(qvariant_cast<QCameraDevice>(ui->deviceComboBox->currentData()));
    });
    connect(this, &CameraSettings::CameraChanged, this, [&](QCamera *device) {
        Q_UNUSED(device)
        connect(camera, &QCamera::cameraDeviceChanged, this, &CameraSettings::UpdateOptions);
        this->UpdateOptions();
    });
}
void CameraSettings::WhiteBalanceConnection() {
    connect(ui->temperatureSlider, &QSlider::valueChanged, camera, &QCamera::setColorTemperature);
    connect(ui->whiteBalanceComboBox, &QComboBox::currentIndexChanged, this, [&](int index) {
        Q_UNUSED(index)
        camera->setWhiteBalanceMode(qvariant_cast<QCamera::WhiteBalanceMode>(ui->whiteBalanceComboBox->currentData()));
    });
    connect(camera, &QCamera::whiteBalanceModeChanged, this, [&]() {
        if(camera->supportedFeatures().testFlag(QCamera::Feature::ColorTemperature)) {
            ui->temperatureLabel->setEnabled(camera->whiteBalanceMode() == QCamera::WhiteBalanceManual);
            ui->temperatureSlider->setEnabled(camera->whiteBalanceMode() == QCamera::WhiteBalanceManual);
        }
    });
}
void CameraSettings::ExposureConnection() {
    connect(ui->exposureCompensationSlider, &QSlider::valueChanged, camera, &QCamera::setExposureCompensation);
    connect(ui->exposureModeComboBox, &QComboBox::currentIndexChanged, [&](int index) {
        Q_UNUSED(index)
        camera->setExposureMode(qvariant_cast<QCamera::ExposureMode>(ui->exposureModeComboBox->currentData()));
    });
}

void CameraSettings::FlashConnection() {
#define CONNECT_FLASH(MODE) \
    connect(ui->flashAutoRadioButton, &QRadioButton::clicked, this, [&]() { \
        if(ui->flash##MODE##RadioButton->isChecked()) { \
            camera->setFlashMode(QCamera::FlashAuto); \
        } \
    });

    CONNECT_FLASH(Auto)
    CONNECT_FLASH(On)
    CONNECT_FLASH(Off)

#undef CONNECT_FLASH

    connect(camera, &QCamera::flashReady, this, [&](bool checked) {
        ui->flashRadyLabel->setText(checked ? "Ready" : "Not Ready");
    });
}
void CameraSettings::UpdateWhiteBalance() {
    ui->whiteBalanceGroup->setEnabled(false);
    ui->whiteBalanceComboBox->clear();
    if(camera == nullptr) {
        return;
    }

#define ADD_WHITE_BALANCE(DESCRIPTION, MODE) \
    if(camera->isWhiteBalanceModeSupported(QCamera::WhiteBalance##MODE)) { \
        ui->whiteBalanceComboBox->addItem(DESCRIPTION, QVariant::fromValue(QCamera::WhiteBalance##MODE)); \
    }

    ADD_WHITE_BALANCE("Auto", Auto)
    ADD_WHITE_BALANCE("Sunlight", Sunlight)
    ADD_WHITE_BALANCE("Cloudy", Cloudy)
    ADD_WHITE_BALANCE("Shade", Shade)
    ADD_WHITE_BALANCE("Tungsten", Tungsten)
    ADD_WHITE_BALANCE("Fluorescent", Fluorescent)
    ADD_WHITE_BALANCE("Flash", Flash)
    ADD_WHITE_BALANCE("Sunset", Sunset)
    ADD_WHITE_BALANCE("Manual", Manual)

#undef ADD_WHITE_BALANCE

    if(ui->whiteBalanceComboBox->count() != 0) {
        ui->whiteBalanceGroup->setEnabled(true);
        ui->whiteBalanceComboBox->setEnabled(true);
        ui->whiteBalanceLabel->setEnabled(true);
    }
    WhiteBalanceConnection();
}

void CameraSettings::UpdateExposure() {
    ui->exposureModeComboBox->clear();
    ui->exposureGroup->setEnabled(false);
    if(camera == nullptr) {
        return;
    }

#define ADD_EXPOSURE(DESCRIPTION, MODE) \
    if(camera->isExposureModeSupported(QCamera::Exposure##MODE)) { \
            ui->exposureModeComboBox->addItem(DESCRIPTION, QVariant::fromValue(QCamera::Exposure##MODE)); \
    }

    ADD_EXPOSURE("Auto", Auto)
    ADD_EXPOSURE("Portrait", Portrait)
    ADD_EXPOSURE("Night", Night)
    ADD_EXPOSURE("Sports", Sports)
    ADD_EXPOSURE("Snow", Snow)
    ADD_EXPOSURE("Beach", Beach)
    ADD_EXPOSURE("Action", Action)
    ADD_EXPOSURE("Landscape", Landscape)
    ADD_EXPOSURE("Night Portrait", NightPortrait)
    ADD_EXPOSURE("Theatre", Theatre)
    ADD_EXPOSURE("Sunset", Sunset)
    ADD_EXPOSURE("Steady Photo", SteadyPhoto)
    ADD_EXPOSURE("Fireworks", Fireworks)
    ADD_EXPOSURE("Party", Party)
    ADD_EXPOSURE("Candlelight", Candlelight)
    ADD_EXPOSURE("Barcode", Barcode)

#undef ADD_EXPOSURE

    ui->exposureCompensationLabel->setEnabled(camera->supportedFeatures().testFlag(QCamera::Feature::ExposureCompensation));
    ui->exposureCompensationSlider->setEnabled(camera->supportedFeatures().testFlag(QCamera::Feature::ExposureCompensation));
    ui->exposureGroup->setEnabled(ui->exposureModeComboBox->count() != 0);
    ExposureConnection();
}

void CameraSettings::UpdateDevices() {
    ui->deviceComboBox->clear();
    ui->deviceComboBox->setEnabled(false);

    auto container = devices.videoInputs();
    for(const auto &value : container) {
        ui->deviceComboBox->addItem(value.description(), QVariant::fromValue(value));
    }

    ui->deviceComboBox->setEnabled(ui->deviceComboBox->count() != 0);
}

void CameraSettings::UpdateOptions() {
    UpdateWhiteBalance();
    UpdateExposure();
    UpdateFlash();
}

void CameraSettings::UpdateFlash() {
    ui->flashGroup->setEnabled(false);
    if(camera == nullptr) {
        return;
    }

#define ADD_FLASH(MODE) \
    ui->flash##MODE##RadioButton->setEnabled(camera->isFlashModeSupported(QCamera::Flash##MODE));

    ADD_FLASH(On)
    ADD_FLASH(Off)
    ADD_FLASH(Auto)

#undef ADD_FLASH

    ui->flashGroup->setEnabled(true);
    FlashConnection();
}

QCamera *CameraSettings::GetCamera() {
    return camera;
}
void CameraSettings::SetCamera(QCamera *value) {
    camera = value;
    emit CameraChanged(camera);
}

CameraSettings::~CameraSettings() {
    delete ui;
}
