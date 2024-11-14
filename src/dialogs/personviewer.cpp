#include "include/dialogs/personviewer.h"
#include "ui_personviewer.h"

PersonViewer::PersonViewer(const Person &person, QWidget *parent) : PersonViewer(parent) {
    this->SetPerson(person);
}

PersonViewer::PersonViewer(QWidget *parent) : QDialog(parent), ui(new Ui::PersonViewer) {
    ui->setupUi(this);

    this->setFixedSize(size);
    connect(ui->editButton, &QPushButton::clicked, this, &PersonViewer::RequestToEdit);

    connect(this, &PersonViewer::PersonChanged, this, &PersonViewer::UpdateTitle);
    UpdateTitle();
}

PersonViewer::~PersonViewer() {
    delete ui;
}

QSize PersonViewer::sizeHint() const {
    return size;
}

void PersonViewer::UpdateTitle() {
    const Person &person = ui->viewer->GetPerson();
    if(person.GetFirstName().isEmpty() || person.GetLastName().isEmpty()) {
        this->setWindowTitle("Unnamed Person");

    } else {
        this->setWindowTitle(person.GetFullName());

    }
}

void PersonViewer::RequestToEdit() {
    emit EditRequested(ui->viewer->GetPerson());
}

Person PersonViewer::GetPerson() const {
    return ui->viewer->GetPerson();
}

void PersonViewer::SetPerson(const Person &person) {
    ui->viewer->SetPerson(person);
    emit PersonChanged(person);
}
