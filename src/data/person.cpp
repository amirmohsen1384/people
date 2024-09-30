#include "../../include/data/person.h"
#include <QPixmap>

void Person::UpdateLastModification()
{
    lastModification = QDateTime::currentDateTime();
    emit LastModificationChanged(lastModification);
}

Person::Person(QObject *parent) : QObject(parent) {
    connect(this, &Person::FirstNameChanged, this, &Person::UpdateLastModification);
    connect(this, &Person::LastNameChanged, this, &Person::UpdateLastModification);
    connect(this, &Person::BirthdayChanged, this, &Person::UpdateLastModification);
    connect(this, &Person::GenderChanged, this, &Person::UpdateLastModification);
    connect(this, &Person::PhotoChanged, this, &Person::UpdateLastModification);
}

Person &Person::operator=(const Person &another) {
    this->SetFirstName(another.GetFirstName());
    this->SetLastName(another.GetLastName());
    this->SetBirthday(another.GetBirthday());
    this->SetGender(another.GetGender());
    this->SetPhoto(another.GetPhoto());
    return *this;
}
Person::Person(const Person &another, QObject *parent) : Person(parent) {
    *this = another;
}

QString Person::GetFirstName() const {
    return this->firstName;

}
void Person::SetFirstName(const QString &value)
{
    this->firstName = value;
    emit FirstNameChanged(this->firstName);
}

QString Person::GetLastName() const {
    return this->lastName;

}
void Person::SetLastName(const QString &value)
{
    this->lastName = value;
    emit LastNameChanged(this->lastName);
}

QDate Person::GetBirthday() const {
    return this->birthday;

}
void Person::SetBirthday(const QDate &value)
{
    this->birthday = value;
    emit BirthdayChanged(value);
}
Person::Gender Person::GetGender() const {
    return this->gender;

}
void Person::SetGender(const Gender &value)
{
    this->gender = value;
    emit GenderChanged(this->gender);
}
QDateTime Person::GetCreation() const {
    return this->creation;

}
QString Person::GetFullName() const
{
    return firstName + ' ' + lastName;
}
QDateTime Person::GetLastModification() const {
    return this->lastModification;

}
QPixmap Person::GetPhoto() const {
    return this->photo;

}
void Person::SetPhoto(const QPixmap &value)
{
    this->photo = value;
    emit PhotoChanged(value);
}
QDataStream& operator<<(QDataStream &stream, const Person &data) {
    stream << data.firstName << data.lastName;
    stream << data.birthday << data.gender;
    stream << data.photo;
    stream << data.creation << data.lastModification;
    return stream;
}
QDataStream& operator>>(QDataStream &stream, Person &data) {
    stream >> data.firstName >> data.lastName;
    stream >> data.birthday >> data.gender;
    stream >> data.photo;
    stream >> data.creation >> data.lastModification;
    return stream;
}
QDebug operator<<(QDebug debugger, const Person &data) {
    debugger = debugger.noquote().nospace();
    debugger << "First name: "       << data.firstName << '\n';
    debugger << "Last name: "        << data.lastName << '\n';
    debugger << "Gender: "           << (data.gender == Person::Gender::Male ? "Male" : "Female") << '\n';
    debugger << "Birthday: "         << data.birthday.toString() << '\n';
    debugger << "Date created: "     << data.creation.toString() << '\n';
    debugger << "Date modified: "    << data.lastModification.toString();
    return debugger;

}
