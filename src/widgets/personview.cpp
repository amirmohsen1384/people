#include "include/widgets/personview.h"
#include "ui_personview.h"

void PersonView::UpdateName() {
    ui->fullName->setText(information.GetFullName());
}

void PersonView::UpdatePhoto() {
    ui->photoView->SetImage(information.GetPhoto().toImage());
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
    connect(&information, &Person::PhotoChanged, this, &PersonView::UpdatePhoto);
    connect(&information, &Person::GenderChanged, this, &PersonView::UpdateGender);
    connect(&information, &Person::LastNameChanged, this, &PersonView::UpdateName);
    connect(&information, &Person::FirstNameChanged, this, &PersonView::UpdateName);
    connect(&information, &Person::BirthdayChanged, this, &PersonView::UpdateBirthday);
    connect(&information, &PersonView::PersonChanged, this, &PersonView::UpdateCreation);
    connect(&information, &Person::LastModificationChanged, this, &PersonView::UpdateLastModification);
}

PersonView::PersonView(Person &value, QWidget *parent) : PersonView(parent) {
    this->SetPerson(value);
}
PersonView::~PersonView() {
    delete ui;
}

Person &PersonView::GetPerson() {
    return information;
}

void PersonView::SetPerson(Person &data) {
    information = data;
    emit PersonChanged(information);
}
