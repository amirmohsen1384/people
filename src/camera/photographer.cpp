#include "include/camera/photographer.h"
#include "ui_photographer.h"

void Photographer::Initialize() {
    session.setCamera(&camera);
    session.setImageCapture(&capture);
    session.setVideoOutput(ui->cameraView);
}
Photographer::Photographer(QWidget *parent) : QDialog(parent), ui(new Ui::Photographer) {
    ui->setupUi(this);
    Initialize();
}
Photographer::~Photographer() {
    delete ui;
}
