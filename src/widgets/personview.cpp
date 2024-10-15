#include "include/widgets/personview.h"
#include "ui_personview.h"

PersonView::PersonView(QWidget *parent) : QWidget(parent), ui(new Ui::PersonView) {
    ui->setupUi(this);
}
PersonView::~PersonView() {
    delete ui;
}
