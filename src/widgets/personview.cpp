#include "include/widgets/personview.h"
#include "ui_personview.h"

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
}

PersonView::PersonView(Person &value, QWidget *parent) : PersonView(parent) {
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
