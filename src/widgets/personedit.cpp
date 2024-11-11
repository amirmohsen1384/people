#include "include/data/firstnamevalidator.h"
#include "include/data/lastnamevalidator.h"
#include "include/camera/photographer.h"
#include "include/widgets/personedit.h"
#include "ui_personedit.h"
#include <QImageReader>
#include <QCloseEvent>
#include <QFileDialog>

// Constructors of the editor
PersonEdit::PersonEdit(QWidget *parent) : QWidget(parent), ui(new Ui::PersonEdit)  {
    ui->setupUi(this);
    ui->firstNameEdit->setValidator(new FirstNameValidator());
    ui->lastNameEdit->setValidator(new LastNameValidator());
    photographer.setAttribute(Qt::WA_DeleteOnClose, false);

    connect(ui->firstNameResetButton, &QPushButton::clicked, this, &PersonEdit::ResetFirstName);
    connect(ui->lastNameResetButton, &QPushButton::clicked, this, &PersonEdit::ResetLastName);
    connect(ui->birthdayResetButton, &QPushButton::clicked, this, &PersonEdit::ResetBirthday);
    connect(ui->genderResetButton, &QPushButton::clicked, this, &PersonEdit::ResetGender);
    connect(ui->photoResetButton, &QPushButton::clicked, this, &PersonEdit::ResetPhoto);

    connect(ui->firstNameEdit, &QLineEdit::inputRejected, this, &PersonEdit::FirstNameRejected);
    connect(ui->lastNameEdit, &QLineEdit::inputRejected, this, &PersonEdit::LastNameRejected);

    connect(ui->cameraButton, &QPushButton::clicked, &photographer, &Photographer::exec);
    connect(ui->fileBrowseButton, &QPushButton::clicked, this, &PersonEdit::NotifyImageBrowser);

    connect(&photographer, &Photographer::AvailableDevicesChanged, this, &PersonEdit::UpdatePhotographerControl);
    connect(&photographer, &Photographer::ImageCaptured, this, &PersonEdit::SetPhoto);

    UpdatePhotographerControl();
    ResetPerson();
}
PersonEdit::PersonEdit(const Person &initial, QWidget *parent) : PersonEdit(parent) {
    this->SetPerson(initial);
}

// These functions are used to retrieve and change the first name
QString PersonEdit::GetFirstName() const {
    return ui->firstNameEdit->text();
}
void PersonEdit::SetFirstName(const QString &value) {
    ui->firstNameEdit->setText(value);
    emit FirstNameChanged(value);
}
void PersonEdit::ResetFirstName() {
    this->SetFirstName(initial.GetFirstName());
}

// These functions are used to retrieve and change the last name
QString PersonEdit::GetLastName() const {
    return ui->lastNameEdit->text();
}
void PersonEdit::SetLastName(const QString &value) {
    ui->lastNameEdit->setText(value);
    emit LastNameChanged(value);
}
void PersonEdit::ResetLastName() {
    this->SetLastName(initial.GetLastName());
}

// These functions are used to retrieve and change the birthday
QDate PersonEdit::GetBirthday() const {
    return ui->birthdayEdit->date();
}
void PersonEdit::SetBirthday(const QDate &value) {
    ui->birthdayEdit->setDate(value);
    emit BirthdayChanged(value);
}
void PersonEdit::ResetBirthday() {
    this->SetBirthday(initial.GetBirthday());
}

// These functions are used to retrieve and change the gender
Person::Gender PersonEdit::GetGender() const {
    if(ui->maleRadioButton->isChecked()) {
        return Person::Gender::Male;

    } else {
        return Person::Gender::Female;

    }
}
void PersonEdit::SetGender(const Person::Gender &value) {
    switch(value) {
        case Person::Gender::Male: {
            ui->maleRadioButton->setChecked(true);
            break;
        }
        case Person::Gender::Female: {
            ui->femaleRadioButton->setChecked(true);
            break;
        }
    }
    emit GenderChanged(value);
}
void PersonEdit::ResetGender() {
    this->SetGender(initial.GetGender());
}

// These functions are used to retrieve and change the photo
void PersonEdit::SetPhoto(const QImage &value) {
    ui->imageView->SetImage(value);
}
QImage PersonEdit::GetPhoto() const {
    return ui->imageView->GetImage();
}
void PersonEdit::ResetPhoto() {
    this->SetPhoto(initial.GetPhoto());
}

// You could use these two functions to retrieve and change the whole information at the time
Person PersonEdit::GetInitialPerson() const {
    return initial;
}
void PersonEdit::SetPerson(const Person &value) {
    this->SetFirstName(value.GetFirstName());
    this->SetLastName(value.GetLastName());
    this->SetBirthday(value.GetBirthday());
    this->SetGender(value.GetGender());
    this->SetPhoto(value.GetPhoto());
}
Person PersonEdit::GetPerson() const {
    Person person;
    person.SetFirstName(this->GetFirstName());
    person.SetLastName(this->GetLastName());
    person.SetBirthday(this->GetBirthday());
    person.SetGender(this->GetGender());
    person.SetPhoto(this->GetPhoto());
    return person;
}
void PersonEdit::ResetPerson() {
    ResetFirstName();
    ResetLastName();
    ResetBirthday();
    ResetGender();
    ResetPhoto();
}

// Destructor of the editor
PersonEdit::~PersonEdit() {
    delete ui;
}

void PersonEdit::closeEvent(QCloseEvent *event) {
    if(photographer.isVisible()) {
        photographer.close();
    }
    event->accept();
}
void PersonEdit::UpdatePhotographerControl() {
    ui->cameraButton->setVisible(!photographer.GetAvailableDevices().isEmpty());
}
void PersonEdit::NotifyImageBrowser() {
    this->SetPhoto(FindImageFile());
}

// This function is used to return a list of supported filter used in image file dialog
QStringList SupportedImageFilters() {
    QStringList container = {};
    container.append("JPEG files (*.jpg *.jpeg)");
    container.append("PNG files (*.png)");
    container.append("BMP files (*.bmp)");
    return container;
}

// This function is used to create a image file dialog and open one
QImage PersonEdit::FindImageFile() {
    QFileDialog dialog(this);
    static QStringList history = {};

    dialog.setWindowTitle("Select a photo to open");
    dialog.setNameFilters(SupportedImageFilters());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(QDir::home());
    dialog.setHistory(history);

    if(dialog.exec() == QDialog::Accepted) {
        QImageReader reader(dialog.selectedFiles().constFirst());
        return reader.read();

    } else {
        return QImage();

    }
}
