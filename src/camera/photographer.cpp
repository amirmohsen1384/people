#include "include/camera/photographer.h"
#include "ui_photographer.h"

Photographer::Photographer(QWidget *parent) : QDialog(parent), ui(new Ui::Photographer) {
    ui->setupUi(this);
}

Photographer::~Photographer() {
    delete ui;
}
