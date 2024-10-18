#include "include/data/firstnamevalidator.h"
#include "include/data/lastnamevalidator.h"
#include "include/camera/photographer.h"
#include "include/widgets/personedit.h"
#include "ui_personedit.h"
#include <QCloseEvent>

// Constructors of the editor
PersonEdit::PersonEdit(QWidget *parent) : QWidget(parent), ui(new Ui::PersonEdit)  {
    ui->setupUi(this);
    photographer.setParent(this);
    ui->firstNameEdit->setValidator(new FirstNameValidator());
    ui->lastNameEdit->setValidator(new LastNameValidator());

    connect(ui->cameraButton, &QPushButton::clicked, this, &PersonEdit::NotifyPhotographer);
    connect(&photographer, &Photographer::AvailableDevicesChanged, this, &PersonEdit::UpdatePhotographerControl);

    connect(ui->firstNameResetButton, &QPushButton::clicked, this, &PersonEdit::ResetFirstName);
    connect(ui->lastNameResetButton, &QPushButton::clicked, this, &PersonEdit::ResetLastName);
    connect(ui->birthdayResetButton, &QPushButton::clicked, this, &PersonEdit::ResetBirthday);
    connect(ui->genderResetButton, &QPushButton::clicked, this, &PersonEdit::ResetGender);
    connect(ui->photoResetButton, &QPushButton::clicked, this, &PersonEdit::ResetPhoto);

    connect(ui->firstNameEdit, &QLineEdit::inputRejected, this, &PersonEdit::FirstNameRejected);
    connect(ui->lastNameEdit, &QLineEdit::inputRejected, this, &PersonEdit::LastNameRejected);



    this->initial = new Person();
    this->SetPerson(this->initial);
}
PersonEdit::PersonEdit(QPointer<Person> initial, QWidget *parent) : PersonEdit(parent) {
    if(!initial.isNull()) {
        this->initial = initial;
    }
    this->SetPerson(this->initial);
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
    this->SetFirstName(initial->GetFirstName());
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
    this->SetLastName(initial->GetLastName());
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
    this->SetBirthday(initial->GetBirthday());
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
            ui->femaleRadioButton->setChecked(false);
            break;
        }
    }
    emit GenderChanged(value);
}
void PersonEdit::ResetGender() {
    this->SetGender(initial->GetGender());
}

// These functions are used to retrieve and change the photo
QPixmap PersonEdit::GetPhoto() const {
    return ui->photoPreview->pixmap();
}
void PersonEdit::SetPhoto(const QPixmap &value) {
    if(!value.isNull()) {
        ui->photoPreview->setPixmap(value);
        emit PhotoChanged(value);
    } else {
        ui->photoPreview->setPixmap(QPixmap(":/images/default.png"));
    }
}
void PersonEdit::ResetPhoto() {
    this->SetPhoto(initial->GetPhoto());
}

// You could use these two functions to retrieve and change the whole information at the time
QPointer<Person> PersonEdit::GetPerson() const {
    QPointer<Person> person = new Person();
    person->SetFirstName(this->GetFirstName());
    person->SetLastName(this->GetLastName());
    person->SetBirthday(this->GetBirthday());
    person->SetGender(this->GetGender());
    person->SetPhoto(this->GetPhoto());
    return person;
}
void PersonEdit::SetPerson(const QPointer<Person> &value) {
    if(value.isNull()) {
        return;
    }
    this->SetFirstName(value->GetFirstName());
    this->SetLastName(value->GetLastName());
    this->SetBirthday(value->GetBirthday());
    this->SetGender(value->GetGender());
    this->SetPhoto(value->GetPhoto());
}
void PersonEdit::ResetPerson() {
    ResetFirstName();
    ResetLastName();
    ResetBirthday();
    ResetGender();
}

const QPointer<Person> PersonEdit::GetInitialPerson() const {
    return initial;
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

void PersonEdit::NotifyPhotographer() {
    if(!photographer.isVisible()) {
        photographer.setVisible(true);
    }
    connect(&photographer, &Photographer::ImageCaptured, [&](const QImage &image) {

        // Will be implemented later

    });
}
