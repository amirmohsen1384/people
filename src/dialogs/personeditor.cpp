#include "include/dialogs/personeditor.h"
#include "ui_personeditor.h"
#include <QScreen>
PersonEditor::PersonEditor(QWidget *parent) : AbstractInterface(parent), ui(new Ui::PersonEditor) {
    ui->setupUi(this);
    UpdateWindow();
    UpdateTitle();
    connect(ui->mainForm, &PersonEdit::InitialChanged, this, &PersonEditor::UpdateTitle);
    connect(ui->controlBox, &QDialogButtonBox::clicked, this, [&](QAbstractButton *button) {
        if(ui->controlBox->buttonRole(button) == QDialogButtonBox::ResetRole) {
            ui->mainForm->ResetPerson();
        }
    });
}
PersonEditor::PersonEditor(const Person &info, QWidget *parent)  : PersonEditor(parent) {
    this->SetPerson(info);
}
PersonEditor::~PersonEditor() {
    delete ui;
}

void PersonEditor::UpdateTitle() {
    const Person &person = ui->mainForm->GetInitial();
    if(person.GetFirstName().isEmpty() || person.GetLastName().isEmpty()) {
        this->setWindowTitle("Unnamed Person");

    } else {
        this->setWindowTitle(person.GetFullName());

    }
}

Person PersonEditor::GetPerson() const {
    return ui->mainForm->GetPerson();
}
void PersonEditor::SetPerson(const Person &person) {
    ui->mainForm->SetInitial(person);
    emit PersonChanged(person);
}

#include <QMessageBox>
void PersonEditor::accept() {
    if(ui->mainForm->GetFirstName().isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "You have not entered the first name.");
        return;

    } else if(ui->mainForm->GetLastName().isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "You have not entered the last name.");
        return;

    } else if(ui->mainForm->GetPhoto().isNull()) {
    QMessageBox::warning(nullptr, "Error", "You have not imported a valid image.");
        return;

    }
    QDialog::accept();
}
