#include "include/widgets/personview.h"
#include "ui_personview.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>

void PersonView::SaveImage() {
    QFileDialog dialog(this);
    static QStringList history = {};

    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(QDir::home());
    dialog.setDefaultSuffix("png");
    dialog.setHistory(history);

    if(dialog.exec() == QDialog::Accepted) {
        QString filename = dialog.selectedFiles().constFirst();
        const QImage &image = information.GetPhoto();
        if(image.save(filename)) {
            history.append(filename);

        } else {
            QMessageBox::critical(this, "Failed to save photo", "The filename might be invalid, or have a non-suitable suffix or format, or there's no permission to save the file here.");

        }
    }
}

void PersonView::UpdatePerson() {
    UpdateName();
    UpdateBirthday();
    UpdateGender();
    UpdatePhoto();
    UpdateCreation();
    UpdateLastModification();
}

void PersonView::UpdateName() {
    ui->fullName->setText(information.GetFullName());
}

void PersonView::UpdatePhoto() {
    ui->imageView->SetImage(information.GetPhoto());
}

void PersonView::UpdateGender() {
    if(information.GetGender() == Person::Gender::Male) {
        ui->genderText->setText("Male");
        ui->genderIcon->setPixmap(QPixmap(":/icons/gender/man.ico"));
    } else {
        ui->genderText->setText("Female");
        ui->genderIcon->setPixmap(QPixmap(":/icons/gender/woman.ico"));
    }
}

void PersonView::UpdateBirthday() {
    ui->birthdayDate->setText(information.GetBirthday().toString());
}

void PersonView::UpdateCreation(){
    ui->creationDate->setText(information.GetCreation().toString());
}

void PersonView::UpdateLastModification() {
    ui->lastModifiedDate->setText(information.GetLastModification().toString());
}

PersonView::PersonView(QWidget *parent) : QWidget(parent), ui(new Ui::PersonView) {
    ui->setupUi(this);
    connect(this, &PersonView::PersonChanged, this, &PersonView::UpdatePerson);
    connect(ui->saveButton, &QPushButton::clicked, this, &PersonView::SaveImage);
}

PersonView::PersonView(const Person &value, QWidget *parent) : PersonView(parent) {
    this->SetPerson(value);
}

PersonView::~PersonView() {
    delete ui;
}

Person PersonView::GetPerson() const {
    return information;
}

void PersonView::SetPerson(const Person &data) {
    information = data;
    emit PersonChanged(information);
}
