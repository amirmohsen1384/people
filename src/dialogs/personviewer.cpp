#include "include/dialogs/personviewer.h"
#include "ui_personviewer.h"

PersonViewer::PersonViewer(const Person &person, QWidget *parent) : PersonViewer(parent) {
    this->SetPerson(person);
}

PersonViewer::PersonViewer(QWidget *parent) : AbstractInterface(parent), ui(new Ui::PersonViewer) {
    ui->setupUi(this);
    UpdateWindow();
    UpdateTitle();
    connect(this, &PersonViewer::PersonChanged, this, &PersonViewer::UpdateTitle);
    connect(ui->editButton, &QPushButton::clicked, this, &PersonViewer::RequestToEdit);
}

PersonViewer::~PersonViewer() {
    delete ui;
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
