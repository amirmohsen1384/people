#include "include/dialogs/personeditdialog.h"
#include "ui_personeditdialog.h"

PersonEditDialog::PersonEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PersonEditDialog) {
    ui->setupUi(this);
    setFixedSize(size);

    connect(ui->mainForm, &PersonEdit::InitialChanged, this, &PersonEditDialog::updateTitle);
    updateTitle();
}
PersonEditDialog::PersonEditDialog(const Person &info, QWidget *parent)  : PersonEditDialog(parent) {
    this->SetPerson(info);
}
PersonEditDialog::~PersonEditDialog() {
    delete ui;
}

QSize PersonEditDialog::sizeHint() const {
    return size;
}
void PersonEditDialog::updateTitle() {
    const Person &person = ui->mainForm->GetInitial();
    if(person.GetFirstName().isEmpty() || person.GetLastName().isEmpty()) {
        this->setWindowTitle("Unnamed Person");

    } else {
        this->setWindowTitle(person.GetFullName());

    }
}

Person PersonEditDialog::GetPerson() const {
    return ui->mainForm->GetPerson();
}
void PersonEditDialog::SetPerson(const Person &person) {
    ui->mainForm->SetInitial(person);
    emit PersonChanged(person);
}

#include <QMessageBox>
void PersonEditDialog::accept() {
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
