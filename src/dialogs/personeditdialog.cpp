#include "include/dialogs/personeditdialog.h"
#include "ui_personeditdialog.h"

PersonEditDialog::PersonEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PersonEditDialog)
{
    ui->setupUi(this);
}

PersonEditDialog::~PersonEditDialog()
{
    delete ui;
}

Person PersonEditDialog::GetPerson() const {
    return ui->mainForm->GetPerson();
}

void PersonEditDialog::SetPerson(const Person &person) {
    ui->mainForm->SetPerson(person);
    emit PersonChanged(person);
}

#include <QMessageBox>
void PersonEditDialog::accept() {
    QMessageBox error;
    error.setParent(this);
    error.setIcon(QMessageBox::Warning);
    error.setStandardButtons(QMessageBox::Ok);
    error.setWindowTitle("Required information has not entered yet.");

    if(ui->mainForm->GetFirstName().isEmpty()) {
        error.setInformativeText("You have not entered your first name.");
        error.exec();
        return;
    }
    if(ui->mainForm->GetLastName().isEmpty()) {
        error.setInformativeText("You have not entered your last name.");
        error.exec();
        return;
    }
    if(ui->mainForm->GetPhoto().isNull()) {
        error.setInformativeText("You have not imported a valid image.");
        error.exec();
        return;
    }

    QDialog::accept();
}
