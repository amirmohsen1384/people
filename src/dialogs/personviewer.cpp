#include "include/dialogs/personviewer.h"
#include "ui_personviewer.h"

PersonViewer::PersonViewer(QWidget *parent) : QDialog(parent), ui(new Ui::PersonViewer) {
    ui->setupUi(this);
}
PersonViewer::~PersonViewer() {
    delete ui;
}
